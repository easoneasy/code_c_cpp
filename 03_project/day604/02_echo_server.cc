
// 套接字地址：
//   struct sockaddr: 通用套接字地址
//   struct sockaddr_in: IPv4套接字地址, family: AF_INET
//   struct sockaddr_in6: IPv6套接字地址, family: AF_INET6
//   struct sockaddr_storage: 存储对端地址
#include <my_header.h>
#include <iostream>
#include <sys/socket.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFHttpServer.h>
#include <workflow/WFTaskFactory.h>

using namespace std;
using namespace protocol;

/*
    客户端发送HTTP请求
        ↓
    服务器收到请求
        ↓
    打印客户端IP和请求序号
        ↓
    把请求内容组织成HTML
        ↓
    返回给浏览器
 */

WFFacilities::WaitGroup waitGroup(1);

void sig_handler(int)
{
    waitGroup.done();
}

void process(WFHttpTask* task)
{
    // 1. 打印客户端地址
    // 获取对端地址
    struct sockaddr_storage addr;
    socklen_t length = sizeof(addr); // 传入传出参数
    // 获取到客户端ip 和 端口号
    task->get_peer_addr((struct sockaddr*)&addr, &length);
    // 套接字地址 --> IP:port
    char ipstr[INET6_ADDRSTRLEN];
    unsigned short port;
    if (addr.ss_family == AF_INET) {
        // IPv4地址
        struct sockaddr_in* sin = (struct sockaddr_in*)&addr;
        inet_ntop(AF_INET, &sin->sin_addr, ipstr, INET6_ADDRSTRLEN);
        port = ntohs(sin->sin_port); // 讲网络字节序转换成主机字节序
    } else if (addr.ss_family == AF_INET6) {
        // IPv6地址
        struct sockaddr_in6* sin6 = (struct sockaddr_in6*)&addr;
        inet_ntop(AF_INET, &sin6->sin6_addr, ipstr, INET6_ADDRSTRLEN);
        port = ntohs(sin6->sin6_port); // 讲网络字节序转换成主机字节序
    } else {
        strcpy(ipstr, "Unknown");
    }
    cout << "[客户端地址] " << ipstr << ": " << port << endl;

    // 2. 打印请求序号 (从0开始编号)
    long long seq = task->get_task_seq();
    cout << "[请求序号] " << seq << endl;

    // 3. 将收到的请求放入响应体
    HttpResponse* resp = task->get_resp();
    resp->set_status_code("200");
    resp->add_header_pair("Server", "My WFHttpServer");
    resp->add_header_pair("Content-Type", "text/html");
    if (seq == 9) {
        // 关闭TCP连接
        // close(sockfd);
        resp->add_header_pair("Connection", "close");
    }
    // 设置响应体
    HttpRequest* req = task->get_req();
    // 特别小心：变量的生命周期
    // resp->append_output_body("<html>");
    resp->append_output_body_nocopy("<html>"); // 静态存储期限

    string line; // 局部变量：自动存储期限
    line = line + "<p>" + req->get_method() + " "
        + req->get_request_uri() + " "
        + req->get_http_version() + "</p>";

    // resp->append_output_body_nocopy(line); // ERROR!
    resp->append_output_body(line);

    HttpHeaderCursor cursor(req);
    string name;
    string value;
    while (cursor.next(name, value)) {
        resp->append_output_body("<p>" + name + ": " + value + "</p>");
    }

    resp->append_output_body_nocopy("</html>");
}

int main()
{
    // 0. 注册信号处理函数
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
