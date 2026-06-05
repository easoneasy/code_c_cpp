#include <iostream>
#include <map>
#include <wfrest/HttpServer.h>

using namespace std;
using namespace wfrest;

void test1()
{
    //1、创建HTTP服务器
    HttpServer server;
    //2、注册路由
    server.GET("/*",[](const HttpReq *req,HttpResp *resp){
        //解析URI ： <path> ? <query>
        cout << req->get_request_uri() << endl;
        //解析<path>
        cout << "full_path:  " << req->full_path() << endl;
        cout << "match_path:  "<< req->match_path() << endl;
        cout << "current_path:  " << req->current_path() << endl;
        //解析查询参数
        const map<string,string> & querys = req->query_list();
        //for循环结构化绑定
        for(const auto &[key,val]:querys)
        {
            cout << key << " : " << val << endl;
        }
    });
    //3、启动服务器
    if(server.start(8888) == 0)
    {
        getchar();
        server.stop();
    }else{
        cerr << "Error : server start failed! " << endl;
        exit(1);
    }
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

