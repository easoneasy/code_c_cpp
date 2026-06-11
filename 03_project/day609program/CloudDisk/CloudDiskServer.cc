#include "CloudDiskServer.h"
#include "CryptoUtil.h"
#include "common.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <wfrest/HttpDef.h>
#include <wfrest/HttpMsg.h>
#include <wfrest/PathUtil.h>
#include <workflow/HttpUtil.h>
#include <workflow/MySQLResult.h>
#include <workflow/Workflow.h>
#include <workflow/mysql_types.h>

using namespace std;
using namespace std::placeholders;
using namespace wfrest;
using namespace protocol;
using json = nlohmann::json;
using namespace AlibabaCloud::OSS;

// 数据库的URL（需要修改！）
static const string DatabaseURL = "mysql://root:123456@localhost/CloudDisk";
static const int RetryMax = 3;
static const string STORAGE_DIR ="./storage";

// 辅助函数
static void send_success(HttpResp *resp,const int status_code,const string msg,const json data)
{
    json body;
    body["status"] = "success";
    body["message"] = msg;
    body["data"] = data;
    resp->set_status(status_code);
    resp->add_header_pair("Content-Type","application/json");
    resp->append_output_body(body.dump());
}
static void send_error(HttpResp *resp,const int status_code,const string msg)
{
    json body;
    body["status"] = "error";
    body["message"] = msg;
    resp->set_status(status_code);
    resp->add_header_pair("Content-Type","application/json");
    resp->append_output_body(body.dump());
}

// 提取token
static string extract_bearer_token(const HttpReq *req,HttpResp *resp)
{
    // 验证身份
    const string &auth = req->header("Authorization");
    // 没有令牌/令牌的类型不是"Bearer"
    if(auth.size() < 8 || auth.substr(0,7) !="Bearer ")
    {
        return "";
    }
    return auth.substr(7);
}

// 验证token，成功返回uid，失败返回-1，并发送错误消息
static int verify_token(const HttpReq *req,HttpResp *resp)
{

    string token = extract_bearer_token(req,resp);
    if(token.empty())
    {
        send_error(resp, 401, "无效的访问令牌");
        return -1;
    }
    User user;
    if(!CryptoUtil::verify_token(token, user))
    {
        send_error(resp, 401, "无效的访问令牌");
        return -1;
    }
    return user.id;
}

static bool ensure_storage_dir()
{
    struct stat st;
    if(stat(STORAGE_DIR.c_str(),&st) != 0)
    {
        return mkdir(STORAGE_DIR.c_str(),0755) == 0;
    }
    return true;
}

// 注册
void register_handler(const HttpReq *req,HttpResp *resp)
{
    // 客户端发错格式(不是json格式)
    if(req->content_type() != wfrest::APPLICATION_JSON)
    {
        resp->set_status(HttpStatusBadRequest);
        json msg = {{"status","error"},{"message","请求格式有误"}};
        resp->append_output_body(msg.dump());
        return;
    }
    // 获取请求体
    // string body = req->body();
    // json data = json::parse(body);
    auto &data = req->json();
    string username = data["username"];
    string password = data["password"];
    string confirm = data["confirm"];

    // 错误校验
    if(confirm != password)
    {
        resp->set_status(HttpStatusBadRequest);
        json msg = {{"status","error"},{"message","两次输入的密码不一致"}};
        resp->append_output_body(msg.dump());
        return;
    }
    if(username.empty() || password.empty())
    {
        resp->set_status(HttpStatusBadRequest);
        json msg={{"status","error"},{"message","用户名和密码不能为空"}};
        resp->append_output_body(msg.dump());
        return;
    }
    // 随机生成盐值
    string salt = CryptoUtil::generate_salt();
    // 将盐值与密码哈希
    string hashcode = CryptoUtil::hash_password(password, salt);
    // 存入数据库，写一个sql语句
    string sql = "insert into tbl_user (username,password,salt) values ('"
        + username +"','"
        + hashcode + "','"
        + salt +"');";
    resp->MySQL(DatabaseURL,sql,[resp,username](MySQLResultCursor *cursor)
        {
            if(cursor->get_cursor_status() == MYSQL_STATUS_OK && cursor->get_affected_rows()==1)
            {
                // 成功
                json data;
                data["userId"]= cursor->get_insert_id();
                data["username"] = username;
                send_success(resp,201,"注册成功",data);
            }else {
                // 失败
                send_error(resp, 409, "用户名已存在");
            }
        });
}

// 登录
void login_handler(const HttpReq *req,HttpResp *resp)
{
    // 判断客户端发送格式
    if(req->content_type() != wfrest::APPLICATION_JSON)
    {
        send_error(resp, 400, "请求格式有误");
        return;
    }
    // 获取请求体
    // string body = req->body();
    // json data = json::parse(body);
    auto &data = req->json();
    string username = data["username"];
    string password = data["password"];
    // 通过用户名查找hashcode、salt
    string sql = "select * from tbl_user where username = '" + username +"';";

    resp->MySQL(DatabaseURL,sql,[resp,password](MySQLResultCursor *cursor)
        {
            if(cursor->get_cursor_status() != MYSQL_STATUS_GET_RESULT ||cursor->get_rows_count()!=1)
            {
                send_error(resp, 500, "内部服务器错误");
                return;
            }
            // 获取数据库中的记录
            vector<MySQLCell> record;
            if(cursor->fetch_row(record))
            {
                User user;
                user.id = record[0].as_int();
                user.username = record[1].as_string();
                user.password = record[2].as_string();
                user.salt = record[3].as_string();
                user.createdAt = record[4].as_datetime();
                // 用户名或密码为空
                if(user.username.empty() || user.password.empty())
                {
                    send_error(resp, 400, "用户名和密码不能为空");
                }
                string hashcode = CryptoUtil::hash_password(password, user.salt);
                if(hashcode == user.password)
                {
                    // 密码校对正确，返回token
                    string token = CryptoUtil::generate_token(user);
                    json data;
                    data["accessToken"] = token;
                    data["tokenType"] = "Bearer";
                    data["user"]["userId"] = user.id;
                    data["user"]["username"] = user.username;
                    send_success(resp, 200, "登录成功", data);
                    return;
                }else{
                    send_error(resp, 401, "用户名或密码错误");
                }
            }
            // 用户不存在/空结果集/密码错误
            // SQL返回空结果集
            send_error(resp, 401, "用户名或密码错误");
        });
}

void user_handler(const HttpReq *req,HttpResp *resp)
{
    // 获取头部的Authorization的值 "Bearer token...."
    const string &auth = req->header("Authorization");
    // 没有令牌/令牌的类型不是"Bearer"
    if(auth.size() < 8 || auth.substr(0,7) != "Bearer ")
    {
        send_error(resp, 401, "无效的访问令牌");
        return;
    }
    // 获取token  去掉"Bearer "
    string token = auth.substr(7);
    // 创建user对象
    User user;
    // 验证token
    // 检查JWT有没有被篡改、解析token的用户数据，填充给user对象
    // 在生成token时，就已经把用户的信息放入token中了，省去了访问数据库的步骤
    if(!CryptoUtil::verify_token(token, user))
    {
        send_error(resp, 401, "无效的访问令牌");
        return;
    }
    // 走到这user对象已经有用户数据了
    // 返回用户信息
    json data;
    data["userId"] = user.id;
    data["username"] = user.username;
    data["createdAt"] = user.createdAt;
    send_success(resp, 200, "获取个人信息成功", data);
}

void file_list_handler(const HttpReq *req,HttpResp *resp)
{
    // 验证身份+token
    int uid = verify_token(req, resp);
    if(uid == -1){return;}

    // 拼接sql语句，查询文件信息
    string sql = "select * from tbl_file where uid = '" + to_string(uid) + "';";
    resp->MySQL(DatabaseURL,sql,[resp](MySQLResultCursor *cursor)
        {
            if(cursor->get_cursor_status()!=MYSQL_STATUS_GET_RESULT)
            {
                send_error(resp, 500, "服务器内部错误");
                return;
            }
            json files = json::array();
            vector<MySQLCell> record;
            while(cursor->fetch_row(record))
            {
                json f;
                f["fileId"] = record[0].as_int();
                f["filename"] = record[2].as_string();
                f["size"] = record[4].as_int();
                f["createdAt"] = record[5].as_datetime();
                f["updatedAt"] = record[6].as_datetime();
                files.push_back(f);
                record.clear();
            }
            json data;
            data["files"] = files;
            send_success(resp, 200, "获取文件列表成功", data);
        });
}
void file_upload_handler(const HttpReq *req,HttpResp *resp)
{
    // 客户端发错格式(不是form格式)
    if(req->content_type() != wfrest::MULTIPART_FORM_DATA)
    {
        resp->set_status(HttpStatusBadRequest);
        json msg = {{"status","error"},{"message","请求格式有误"}};
        resp->append_output_body(msg.dump());
        return;
    }
    // 验证身份+token
    int uid = verify_token(req, resp);
    if(uid == -1){return;}
    // 解析请求体，拿到文件名、文件内容
    // wfrest使用pair<文件名，文件内容> 存储
    // 将前端数据解析成form对象   --> map<string,<string,string>>
    const Form &form = req->form();
    // 将form对象解析成file对象  --> pair<string,string>
    // form中包含多个file对象
    // const 只读    & 避免复制
    const auto &file = form.at("file");
    // file.first --> 文件名
    // file.second --> 文件内容
    string filename = file.first;
    string file_data = file.second;
    // 判断文件名/文件内容是否为空
    if(filename.empty() || file_data.empty())
    {
        send_error(resp, 400, "请求格式有误");
        return;
    }
    // 计算文件的哈希值
    string hashcode = CryptoUtil::generate_hashcode(file_data.c_str(), file_data.size());
    // 判断存储目录是否存在
    // ensure_storage_dir();
    // 本地存储文件
    // string basename = STORAGE_DIR +"/" + hashcode;
    // resp->Save(basename,file_data);
    // 单例对象，将文件的哈希与文件内容传给单例对象
    // 上传到云存储
    bool isUpload = OSSManager::getInstance().upload(hashcode, file_data);
    if(!isUpload)
    {
        send_error(resp, 400, "云备份失败");
        return;
    }
    //
    // 插入数据库
    string sql = "insert into tbl_file (uid,filename,hashcode,size) values("
        + to_string(uid) +",'" + filename +"','" + hashcode +"'," +to_string(file_data.size()) +")";
    resp->MySQL(DatabaseURL,sql,[resp,filename](MySQLResultCursor *cursor)
        {
            if(cursor->get_cursor_status() == MYSQL_STATUS_OK && cursor->get_affected_rows() == 1)
            {
                // 成功
                json data;
                data["fileId"] = cursor->get_insert_id();
                data["filename"] = filename;
                send_success(resp, 201, "上传成功", data);
            }else
            {
                // 失败
                send_error(resp, 500, "内部服务器错误");
            }
        });

}
void file_download_handler(const HttpReq *req,HttpResp *resp)
{
    // 验证身份 + token
    int uid = verify_token(req,resp);
    if(uid == -1){return;}

    // 解析请求头的文件id
    string file_id = req->param("id");
    if(file_id.empty())
    {
        send_error(resp, 400, "请求格式有误");
        return;
    }
    // 查数据库
    string sql = "select uid,filename,hashcode from tbl_file where id = '" + file_id +"'";
    resp->MySQL(DatabaseURL,sql,[resp,uid](MySQLResultCursor *cursor)
        {
            if(cursor->get_cursor_status()!=MYSQL_STATUS_GET_RESULT )
            {
                send_error(resp, 500, "服务器内部错误");
                return;
            }
            vector<MySQLCell> record;
            if(!cursor->fetch_row(record))
            {
                send_error(resp, 404, "文件不存在");
                return;
            }
            int db_uid = record[0].as_int();
            string db_filename = record[1].as_string();
            string db_hashcode = record[2].as_string();
            // 检查文件归属
            if(db_uid != uid)
            {
                send_error(resp,404, "文件不存在");
                return;
            }
            string file_data;
            // 读盘
            // resp->File(STORAGE_DIR + "/" + db_hashcode);
            bool isDownload = OSSManager::getInstance().download(db_hashcode,file_data);
            if(!isDownload)
            {
                send_error(resp, 500, "云下载失败");
                return;
            }
            resp->String(file_data);
        });
}


void CloudDiskServer::register_routes()
{
    // 设置静态资源的路由
    register_www_module();
    register_auth_module();
    register_user_module();
    register_file_module();
}

void CloudDiskServer::register_www_module()
{
    server_.Static("/", "./www/index.html");
    server_.Static("/static", "./www/static");
}

// 注册认证模块的路由
void CloudDiskServer::register_auth_module()
{
    server_.POST("/api/v1/auth/register",register_handler);
    server_.POST("/api/v1/auth/login",login_handler);
}

void CloudDiskServer::register_user_module()
{
    server_.GET("/api/v1/user/me",user_handler);
}

void CloudDiskServer::register_file_module()
{
    server_.GET("/api/v1/files",file_list_handler);
    server_.POST("/api/v1/files",file_upload_handler);
    server_.GET("/api/v1/file/{id}",file_download_handler);
}
