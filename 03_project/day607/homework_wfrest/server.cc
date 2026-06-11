#include "CryptoUtil.h"
#include <csignal>
#include <iostream>
#include <vector>
#include <wfrest/HttpDef.h>
#include <wfrest/HttpMsg.h>
#include <wfrest/HttpServer.h>
#include <wfrest/PathUtil.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/mysql_types.h>
#include <workflow/MySQLResult.h>

using namespace std;
using namespace wfrest;
using namespace protocol;

static const char *DataBaseURL = "mysql://root:123456@localhost/demo";

static WFFacilities::WaitGroup waitGroup(1);

void sig_handler(int)
{
    waitGroup.done();
}
void register_handler(const HttpReq *req,HttpResp *resp)
{
    // 获取用户名、密码
    auto &data = req->form_kv();
    string username = data["username"];
    string password = data["password"];
    // 生成salt
    string salt = CryptoUtil::generate_salt();

    // 密码+salt --> 哈希
    string hashcode = CryptoUtil::hash_password(password, salt);
    // 拼SQL语句插入用户名、密码、salt
    string sql = "insert into tbl_user " "(username,password,salt)""values('"
        +username + "','" + hashcode + "','"+salt + "');";
    // 执行SQL
    resp->MySQL(DataBaseURL,sql,[resp](MySQLResultCursor *cursor)
        {
            // 处理注册结果
            if(cursor->get_cursor_status() != MYSQL_STATUS_ERROR && cursor->get_affected_rows() ==1)
            {
                resp->String("register success!");
            }else{
                resp->set_status(HttpStatusBadRequest);
                resp->String("register failed!");
            }
        });
    // 返回结果
}
void login_handler(const HttpReq *req,HttpResp *resp)
{
    // 解析请求，获取用户名、密码
    if(req->content_type() != APPLICATION_URLENCODED)
    {
        resp->set_status(HttpStatusBadRequest);
        return;
    }
    map<string,string> &data = req->form_kv();
    string username = data["username"];
    string password = data["password"];
    // 查询数据库
    string sql = "select * from tbl_user where username= '" + username + "';";
    resp->MySQL(DataBaseURL,sql,[resp,password](MySQLResultCursor *cursor)
        {
            if(cursor->get_cursor_status() != MYSQL_STATUS_GET_RESULT || cursor->get_rows_count() != 1)
            {
                resp->set_status(HttpStatusBadRequest);
                resp->String("login failed,username or password failed");
                return;
            }
            vector<MySQLCell> record;
            if(cursor->fetch_row(record))
            {
                // 获取mysql表中的用户信息
                User user;
                user.id = record[0].as_int();
                user.username = record[1].as_string();
                user.password = record[2].as_string();
                user.salt = record[3].as_string();
                user.createdAt = record[4].as_datetime();
                // 根据查到的salt和password ，hash一次对比数据库的密码
                string hashcode = CryptoUtil::hash_password(password, user.salt);
                if(hashcode == user.password)
                {
                    resp->String(user.username + "Welcome!\n");
                    resp->String(CryptoUtil::generate_token(user));
                    return;
                }
            }
            resp->set_status(HttpStatusBadRequest);
            resp->String("Username or Password failed\n");
        });

}
void file_handler(const HttpReq *req,HttpResp *resp)
{
    // 获取token
    string authHeader = req->header("Authorization");
    if(authHeader.empty() || authHeader.find("Bearer") != 0)
    {
        resp->set_status(HttpStatusUnauthorized);
        resp->String("authorization failed\n");
        return;
    }
    // 验证token
    User user;
    string token = authHeader.substr(7);
    if(!CryptoUtil::verify_token(token,user))
    {
        resp->set_status(HttpStatusUnauthorized);
        resp->String("authorization failed\n");
        return;
    }
    // 获取文件路径
    string path = req->current_path();
    if(path == "/")
    {
        path += "index.html";
    }
    path = "resources" + path;
    // 返回文件
    string filename = PathUtil::base(path);
    resp->add_header_pair("Content-Disposition","attachment;filename="+filename);
    resp->File(path);
}

int main(int argc,char *argv[])
{
    signal(SIGINT,sig_handler);

    HttpServer server;

    // 注册路由
    // 注册
    server.POST("/register",register_handler);
    // 登录
    server.POST("/login",login_handler);
    // 下载文件
    server.GET("/*",file_handler);

    if(server.start(8888) == 0)
    {
        waitGroup.wait();
        server.stop();
    }

    return 0;
}
