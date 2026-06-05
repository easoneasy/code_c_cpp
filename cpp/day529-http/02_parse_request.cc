#include <iostream>
#include <wfrest/HttpServer.h>
#include <workflow/HttpUtil.h>

using namespace std;
using namespace protocol;
using namespace wfrest;

void test1()
{
    //1、创建httpserver
    HttpServer server;
    //2、注册路由
    //get请求
    server.GET("/*",[](const HttpReq* req,HttpResp *resp){
        //解析请求
        cout << req->get_method() << " "
        << req->get_request_uri() << " "
        << req->get_http_version() << "\r\n";
        //解析请求头
        HttpHeaderCursor cursor(req);
        string name;
        string value;
        while(cursor.next(name,value))
        {
            cout << name << " : " << value << endl;
        }
        cout << "\r\n";
    });
    //post请求
    server.POST("/*",[](const HttpReq* req,HttpResp* resp){
        //解析请求
        cout << req->get_method() << " "
        << req->get_request_uri() << " "
        << req->get_http_version() << "\r\n";
        //解析请求头
        HttpHeaderCursor cursor(req);
        string name;
        string value;
        while(cursor.next(name,value))
        {
            cout << name << " : " << value << endl;
        }
        cout << "\r\n";
        //解析请求体

        cout << req->body() << endl;
    });
    //3、启动服务器：绑定通配符地址，监听8888端口
    if(server.start(8888) == 0)
    {
        getchar();
        server.stop();
    }else
    {
        cerr << "Error : server start failed." << endl;
    }
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

