#include <arpa/inet.h>
#include <csignal>
#include <iostream>
#include <mysql/mysql.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFHttpServer.h>
#include <workflow/WFTaskFactory.h>

using namespace std;
using namespace protocol;

/*
    浏览器
    |
    | HTTP请求
    v
    WFHttpServer
    |
    v
    process()
    |
    v
    生成HTTP响应
    |
    v
    浏览器
 */

WFFacilities::WaitGroup waitGroup(1);

void sig_handler(int)
{
    waitGroup.done();
}
// 请求处理函数
void process(WFHttpTask *httpTask)
{
    // 获取对端的地址
    // sockaddr_storage 能装两种地址
    struct sockaddr_storage addr;
    socklen_t length = sizeof(addr);

    httpTask->get_peer_addr((struct sockaddr*)&addr,&length);

    char ipstr[INET6_ADDRSTRLEN];  // ip
    unsigned short port;            // port

    if(addr.ss_family == AF_INET)
    {
        // ipv4
        struct sockaddr_in *sin = (struct sockaddr_in*)&addr;
        // 二进制的ip转成字符串ip
        inet_ntop(AF_INET, &sin->sin_addr, ipstr, INET6_ADDRSTRLEN);
        // 网络字节序 --> 主机字节序
        port = ntohs(sin->sin_port);
    }else if(addr.ss_family == AF_INET6)
    {
        // ipv6
        struct sockaddr_in6 *sin6 = (struct sockaddr_in6*)&addr;
        inet_ntop(AF_INET6,&sin6->sin6_addr,ipstr,INET6_ADDRSTRLEN);
        port = ntohs(sin6->sin6_port);
    }else{
        strcpy(ipstr,"Unknow");
    }
    cout << "[客户端地址]" << ipstr << " : " << port << endl;

    // 请求编号 从0开始
    long long seq = httpTask->get_task_seq();
    cout << "[请求序号]" << seq << endl;

    // 获取响应对象
    HttpResponse *resp = httpTask->get_resp();
    // 设置状态码
    resp->set_status_code("200");
    // 添加响应头
    resp->add_header_pair("server","My WFHttpServer");
    resp->add_header_pair("Content-Type","text/html");
    // 第10个请求就关闭连接
    if(seq == 9)
    {
        resp->add_header_pair("Connection","close");
    }
    // 获取请求对象
    HttpRequest *req = httpTask->get_req();
    // _nocopy "<html>" 是字符串常量，存储在静态存储区，程序结束前都一直存在
    // 生命周期大于当前函数周期
    resp->append_output_body_nocopy("<html>");
    string line;
    // 获取请求方法
    line = line +"<p>" + req->get_method() + " "
        // 获取URI
        + req->get_request_uri() + " "
        // 获取协议版本
        + req->get_http_version() + "</p>";
    // 没有_nocopy line是局部变量，当前函数结束内存失效
    // nocopy是保存指针，没有复制内容，当后面发送响应line失效，nocpy保存的指针变成了野指针，程序崩溃
    // 所以这个需要复制，不能用nocopy
    resp->append_output_body(line);

    // 遍历http请求头，写入响应头
    HttpHeaderCursor cursor(req);
    string name;
    string value;
    while(cursor.next(name,value))
    {
        resp->append_output_body("<p>" + name + ":" +value+"</p>");
    }
    resp->append_output_body_nocopy("</html>");
}

int main(int argc,char *argv[])
{
    // 注册 Ctrl + c 信号
    signal(SIGINT,sig_handler);
    // 创建服务器，调用process
    WFHttpServer server(process);
    // 启动监听
    if(server.start(8888) == 0)
    {
        // 主线程阻塞
        waitGroup.wait();
        // 服务器退出
        server.stop();
    }else{
        // 启动监听失败
        cerr << "Error : server start failed " << endl;
    }

    return 0;
}
