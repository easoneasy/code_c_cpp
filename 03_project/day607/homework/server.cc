#include "CryptoUtil.h"
#include <csignal>
#include <iostream>
#include <sys/types.h>
#include <workflow/HttpMessage.h>
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

    string uri = req->get_request_uri();
    // 解析uri中的username 和 password
    string username;
    string password;
    // 找到?后的内容是key=value
    auto begin_pos = uri.find('?');
    auto key1_pos = uri.find('=');
    username = uri.substr(begin_pos+1,key1_pos-begin_pos-1);
    // 找到最后一个=，一直切到末尾
    auto last_pos = uri.find_last_of('=');
    password = uri.substr(last_pos+1);
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

// 登录
void do_login(WFHttpTask *httptask)
{
    // 解析URI中的用户名和密码
    HttpRequest *req = httptask->get_req();
    HttpResponse *resp = httptask->get_resp();
    string uri = req->get_request_uri();

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
