#include "CryptoUtil.h"
#include <cassert>
#include <csignal>
#include <cstddef>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <workflow/MySQLMessage.h>
#include <workflow/MySQLResult.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFHttpServer.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>
#include <workflow/mysql_types.h>

using namespace std;
using namespace protocol;

struct Context
{
    HttpResponse *httpResp;
    string username;
    string password;
};

WFFacilities::WaitGroup waitGroup(1);

void sig_handler(int)
{
    waitGroup.done();
}
// 注册的回调函数
void register_callback(WFMySQLTask *mysqlTask)
{
    // 从当前任务所在序列中，把之前存进去的上下文拿出来
    Context *ctx = static_cast<Context*>(series_of(mysqlTask)->get_context());
    // 1、检查网络/MySQL服务器是否正常
    int state = mysqlTask->get_state();
    if(state != WFT_STATE_SUCCESS)
    {
        ctx->httpResp->set_status_code("500");
        ctx->httpResp->append_output_body_nocopy("<html>Inernal Server Error</html>");
        return;
    }

    // SQL执行是否正确
    if(mysqlTask->get_resp()->get_packet_type()==MYSQL_PACKET_ERROR)
    {
        ctx->httpResp->set_status_code("400");
        ctx->httpResp->append_output_body_nocopy("<html>username already exist</html>");
        return;
    }
    // 成功返回注册成功
    ctx->httpResp->append_output_body_nocopy("Register success!");
}

// 注册
void do_register(WFHttpTask *httpTask)
{
    HttpRequest *req = httpTask->get_req();
    HttpResponse *resp = httpTask->get_resp();

    // 获取请求体的内容
    const void *body;
    size_t size;
    req->get_parsed_body(&body,&size);
    string content = static_cast<const char*>(body);

    auto key1_pos = content.find_first_of('=');  // 第一个等号
    auto key2_pos = content.find_last_of('=');   // 第二个等号
    auto and_pos = content.find('&');
    string username = content.substr(key1_pos+1,and_pos-key1_pos-1);
    string password = content.substr(key2_pos+1);
    cout << "username : " << username << endl;
    cout << "password : " << password << endl;

    // 加密密码  生成8位随机盐值
    string salt = CryptoUtil::generate_salt();
    // 混合哈希
    string hashcode = CryptoUtil::hash_password(password, salt);

    // 拼接SQL语句
    string sql = "insert into tbl_user (username,password,salt) values('"
        + username +"', '" + hashcode + "','" +salt+"');";

    // 创建MySQL任务
    string url = "mysql://root:123456@localhost/demo";
    WFMySQLTask *mysqlTask = WFTaskFactory::create_mysql_task(url,3,register_callback);
    // 在mysqlTask的请求任务中，塞入具体的SQL语句
    // 连接数据库，执行这个sql语句
    mysqlTask->get_req()->set_query(sql);

    // 绑定上下文
    Context *ctx = new Context{httpTask->get_resp(),username,password};
    // 获取当前请求的任务序列
    SeriesWork *series = series_of(httpTask);
    // 把上下文存储到序列中
    series->set_context(ctx);

    // 设置序列清理函数
    series->set_callback([ctx](const SeriesWork*)
        {
            delete ctx;
        });

    // 把Mysql任务推入序列，Workflow自动执行
    series->push_back(mysqlTask);
}

void login_callback(WFMySQLTask *mysqlTask)
{
    Context *ctx = static_cast<Context*>(series_of(mysqlTask)->get_context());
    MySQLResponse *resp= mysqlTask->get_resp();
    // 检查网络状态
    int state = mysqlTask->get_state();
    if(state != WFT_STATE_SUCCESS)
    {
        ctx->httpResp->set_status_code("500");
        ctx->httpResp->append_output_body_nocopy("<html>Internal Server Failed</html>");
        return;
    }
    // 检查SQL语句执行
    if(mysqlTask->get_resp()->get_packet_type() == MYSQL_PACKET_ERROR)
    {
        ctx->httpResp->set_status_code("400");
        ctx->httpResp->append_output_body_nocopy("<html>Username is not exist</html>");
        return;
    }
    // 用游标读取数据库结果
    MySQLResultCursor cursor(resp);
    // 存储一行数据
    vector<MySQLCell> record;
    // 如果fetch_row返回true，说明查到了这个用户
    if(cursor.fetch_row(record))
    {
        User user;
        user.id = record[0].as_int();
        user.username = record[1].as_string();
        // 拿到数据库里存储的正确的哈希密码和盐值
        user.password = record[2].as_string();
        user.salt = record[3].as_string();
        // 对比密码
        string hashcode = CryptoUtil::hash_password(ctx->password, user.salt);
        // 密码一致
        if(hashcode == user.password)
        {
            // 登录成功
            // 回一句欢迎登录
            string body = user.username + ", Welcome \n";
            ctx->httpResp->append_output_body(body);
            // 签发Token并追加到响应体中
            ctx->httpResp->append_output_body(CryptoUtil::generate_token(user));
            return;
        }
    }
    // 要么没这个用户，要么密码错误
    ctx->httpResp->set_status_code("400");
    ctx->httpResp->append_output_body_nocopy("<html>Username or Password failed</html>");
}

// 登录
void do_login(WFHttpTask *httptask)
{
    // 解析URI中的用户名和密码
    HttpRequest *req = httptask->get_req();
    HttpResponse *resp = httptask->get_resp();
    // 获取请求体的内容
    const void *body;
    size_t size;
    req->get_parsed_body(&body,&size);
    string content = static_cast<const char*>(body);

    auto key1_pos = content.find_first_of('=');  // 第一个等号
    auto key2_pos = content.find_last_of('=');   // 第二个等号
    auto and_pos = content.find('&');
    string username = content.substr(key1_pos+1,and_pos-key1_pos-1);
    string password = content.substr(key2_pos+1);
    cout << "username : " << username << endl;
    cout << "password : " << password << endl;

    // 拼接查询sql语句
    string sql = "select * from tbl_user where username = '" + username + "'";
    // 创建Mysql任务
    string url = "mysql://root:123456@localhost/demo";
    WFMySQLTask *mysqlTask = WFTaskFactory::create_mysql_task(url,3,login_callback);

    // 把查询语句写入mysql请求体
    mysqlTask->get_req()->set_query(sql);

    // 绑定上下文
    SeriesWork *series = series_of(mysqlTask);
    Context *ctx = new Context{httptask->get_resp(),username,password};
    series->set_context(ctx);
    series->set_callback([ctx](const SeriesWork*){delete ctx;});
    series->push_back(mysqlTask);
}

void pread_callback(WFFileIOTask *preadTask,HttpResponse *resp,string filename)
{
    // 拿到传入的参数
    FileIOArgs *args = preadTask->get_args();
    // 关闭文件描述符
    close(args->fd);
    // 读取的字节数
    long bytes = preadTask->get_retval();
    if(preadTask->get_state() != WFT_STATE_SUCCESS)
    {
        resp->set_status_code("500");
        resp->append_output_body_nocopy("<html>Internal Server Error</html>");
    }else{
        resp->add_header_pair("Content-Disposition","attachment;filename="+filename);
        resp->append_output_body_nocopy(args->buf,bytes);
    }

}

void do_send(WFHttpTask *httpTask)
{
    // 验证token
    HttpRequest *req = httpTask->get_req();
    HttpResponse *resp = httpTask->get_resp();
    HttpHeaderCursor cursor(req);
    string value;
    cursor.find("Authorization",value);
    string token = value.substr(value.find(' ')+1);
    User user;
    // 如果没有token/超时/伪造
    if(!CryptoUtil::verify_token(token, user))
    {
        resp->set_status_code("401");
        resp->append_output_body_nocopy("<html>401 Unauthorized</html>");
        return;
    }
    cout << "认证通过" << endl;

    // 准备文件
    // 解析uri 获取文件路径
    string uri = req->get_request_uri();
    string path = uri.substr(0,uri.find('?'));
    if(path == "/")
    {
        path += "index.html";
    }
    path = "resources" + path;
    // 获取文件名
    string filename = path.substr(path.find_last_of('/')+1);
    // 判断文件是否可访问
    if(access(path.c_str(), R_OK) == -1)
    {
        resp->set_status_code("404");
        resp->append_output_body_nocopy("<html>404 Not Found</html>");
        return;
    }
    // 文件存在且有读取权限
    int fd = open(path.c_str(),O_RDONLY);
    if(fd == -1)
    {
        resp->set_status_code("500");
        resp->append_output_body_nocopy("<html>Internal Server failed</html>");
        return;
    }
    // 打开成功，获取文件大小
    size_t size = lseek(fd, 0, SEEK_END);
    // 在堆上申请buff
    void *buf = malloc(size);
    assert(buf != nullptr && "malloc failed");
    // 创建异步读取任务
    httpTask->set_callback([buf](WFHttpTask *task){
        free(buf);
    });
    // 创建preadTask
    WFFileIOTask *preadTask = WFTaskFactory::create_pread_task(
        fd,buf,size,0,
        bind(pread_callback,placeholders::_1,resp,filename)
    );
    // 将preadTask添加到httpTask所在序列中
    series_of(httpTask)->push_back(preadTask);
}


void process(WFHttpTask *httpTask)
{
    HttpRequest *req = httpTask->get_req();
    HttpResponse *resp = httpTask->get_resp();

    // 获取请求方法和请求的URI
    string method = req->get_method();
    string uri = req->get_request_uri();
    string path;

    // 截掉问号后面的参数，拿到纯粹的路径
    auto pos = uri.find('?');
    if(pos == string::npos){
        path = uri;
    }else {
        path = uri.substr(0,pos);
    }

    // 根据方法和路径分发
    if(method == "POST")
    {
        if(path == "/login"){
            // 登录任务
            //do_login(httpTask);
        }else if(path == "/register"){
            // 注册任务
            do_register(httpTask);
        }else{
            // 匹配不到路径
            resp->set_status_code("404");
            resp->append_output_body_nocopy("<html>404 Not Found</html>");
        }
    }else if (method == "GET") {
        // 处理静态资源下载
        //do_send(httpTask);
    }else{
        resp->set_status_code("405");
    }

}

int main(int argc,char *argv[])
{
    // 注册信号处理函数
    signal(SIGINT,sig_handler);
    // 创建服务器对象
    WFHttpServer server(process);
    // 启动服务器监听8888端口
    if(server.start(8888) == 0)
    {
        cout << "Server started on port 8888" << endl;
        waitGroup.wait();
        server.stop();
    }else{
        cerr << "Server start failed" << endl;
        return 1;
    }

    return 0;
}
