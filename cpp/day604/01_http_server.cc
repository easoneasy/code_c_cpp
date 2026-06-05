#include <iostream>
#include <signal.h>
#include <workflow/HttpMessage.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFHttpServer.h>
#include <workflow/WFTaskFactory.h>

using namespace std;
using namespace protocol;

WFFacilities::WaitGroup waitGroup(1);

void sig_handler(int)
{
    waitGroup.done();
}

void process(WFHttpTask* task)
{
    HttpResponse* resp = task->get_resp();
    // resp->append_output_body("Hello workflow!");

    // 解析请求
    HttpRequest* req = task->get_req();
    string method = req->get_method();
    string uri = req->get_request_uri();
    // cout << method << ": " << uri << endl;
    // 获取用户输入的路径
    auto pos = uri.find('?');
    string path = uri.substr(0, pos);
    // cout << "path: " << path << endl;

    // 分发请求
    if (method == "GET") {
        if (path == "/hello") {
            resp->append_output_body("Hello world!\n");
        } else if (path == "/lover") {
            resp->append_output_body("Peanut loves xixi\n");
        } else {
            resp->set_status_code("404");
            resp->append_output_body("404 NOT FOUND\n");
        }
    }
}

int main()
{
    signal(SIGINT, sig_handler);
    // 1. 创建HTTP服务器
    WFHttpServer server(process);

    // 2. 启动服务器：绑定通配符地址，监听8888端口
    if (server.start(8888) == 0) {
        // 让主线程阻塞
        waitGroup.wait();
        server.stop();
    } else {
        cerr << "Error: Server start FAILED!" << endl;
    }
}
