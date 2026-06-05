#include <iostream>
#include <wfrest/HttpServer.h>
#include <workflow/HttpUtil.h>

using namespace std;
using namespace wfrest;
/*
    重定向
    301 moved permanently ：永久重定向
    303 see other：跳转到结果页，第二次请求一定是GET方法
    307 temporary redirect：临时重定向，保持请求方法不变

*/
void test1()
{
    // 1、创建HTTP服务器
    HttpServer server;
    // 2、注册路由

    //-----------------------301-----------------------------------

    server.GET("/status/301",[](const HttpReq *req,HttpResp* resp)
    {
        //解析请求，处理业务，生成响应
        resp->set_status(301);
        resp->set_header_pair("Location","/newpage/301");
    });
    server.GET("newpage/301",[](const HttpReq *rep,HttpResp* resp)
    {
        //设置响应体
        resp->String("GET /newpage/301");
    });

    //------------------------303--------------------------------

    server.GET("/status/303",[](const HttpReq *req,HttpResp *resp)
    {
        resp->set_status(303);
        //设置URI，没有设置请求方法
        resp->set_header_pair("Location","/newpage/303");
    });
    server.POST("/status/303",[](const HttpReq *req,HttpResp *resp)
    {
        resp->set_status(303);
        resp->set_header_pair("Location","/newpage/303");
    });
    //设置响应体
    server.GET("/newpage/303",[](const HttpReq *req,HttpResp *resp)
    {
        resp->String("GET /newpage/303");
    });
    server.POST("/newpage/303",[](const HttpReq *req,HttpResp *resp)
    {
        resp->String("POST /newpage/303");
    });

    //-----------------------307--------------------------------

    server.GET("/status/307",[](const HttpReq *req,HttpResp *resp)
    {
        resp->set_status(307);
        resp->set_header_pair("Location","/newpage/307");
    });
    server.POST("/status/307",[](const HttpReq *req,HttpResp *resp)
    {
        resp->set_status(307);
        resp->set_header_pair("Location","/newpage/307");
    });
    //设置响应体
    server.GET("/newpage/307",[](const HttpReq *req,HttpResp *resp)
    {
        resp->String("GET /newpage/307");
    });
    server.POST("/newpage/307",[](const HttpReq *req,HttpResp *resp)
    {
        resp->String("POST /newpage/307");
    });

    // 3、启动服务器
    if(server.start(8888) == 0)
    {
        getchar();
        server.stop();
    }else{
        cerr << "Error : Server start failed " << endl;
    }

}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

