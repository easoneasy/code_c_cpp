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
using namespace placeholders;

WFFacilities::WaitGroup waitGroup(1);

void sig_handler(int)
{
    waitGroup.done();
}

void pread_callback(WFFileIOTask *task,HttpResponse *resp,string filename)
{
    // 1、获取参数和返回值
    //FileIOArgs 是一个结构体
    // 里面存放文件描述符、缓冲区指针（输出存放位置）、写入/读取的字节数、从文件的哪个位置开始读取
    FileIOArgs *args = task->get_args();
    // 进入这个函数时，文件已经读取完毕
    // 在process里打开了文件，需要关闭文件,否则会造成文件泄漏
    close(args->fd);
    // 获取返回值 ，获取实际读取的字节数目
    long bytes = task->get_retval();

    // 2、判断任务的状态
    int state = task->get_state();
    if(state != WFT_STATE_SUCCESS)
    {
        cerr << WFGlobal::get_error_string(state,task->get_error()) << endl;
        resp->set_status_code("500");
        resp->append_output_body("<html>");
        return;
    }

    // 3、将文件内容（buf） 追加到响应体中
    // 考虑生命周期 _nocopy ： 保证args->buf 的生命周期 > httptask
    // 不显示内容，作为附件处理，直接下载文件
    resp->add_header_pair("Content-Disposition","attachment;filename=" + filename);
    // 直接引用buf的内容，不拷贝，因为文件可能很大，会浪费时间和内存
    // 这块内存在整个HTTP响应发送完之前必须保持有效
    // 如果提前释放会导致HttpResponse持有悬空指针，发送响应时可能会乱码
    // 把free(buff)放在httptask的回调函数中执行，保证响应发送完成之后再释放内存
    resp->append_output_body_nocopy(args->buf,bytes);
}

void process(WFHttpTask *httptask)
{
    // 请求：GET方法  /URI  http/1.1
    // 1、解析请求
    // 获取路径
    HttpRequest *req = httptask->get_req();
    string uri = req->get_request_uri();
    auto pos = uri.find('?');
    string path = uri.substr(0,pos);  // 获取路径
    cout << "[path] : " << path << endl;
    //本地路径映射
    if(path == "/")
    {
        path += "index.html";
    }
    path = "resources" + path;
    // 输出文件的路径
    cout << "[path] : " << path << endl;

    // 获取文件名  从最后的/可以获取文件名
    pos = path.find_last_of('/');
    string filename = path.substr(pos + 1);
    cout << "[filename] : " << filename << endl;

    // 2、打开文件，读取文件，放在响应体中，返回给客户端
    // pread读取文件内容
    //创建pread任务
    HttpResponse *resp = httptask->get_resp();
    resp->add_header_pair("Server","Sogou C++ Workflow Server");

    int fd = open(path.c_str(),O_RDONLY);
    // assert(fd != -1 && "open failed");
    // 没有此文件/文件打开失败，向客户端返回404 Not Found
    if(fd == -1)
    {
        resp->set_status_code("404");
        resp->append_output_body("<html>404 Not Found</html>");
        return;
    }
    //count : 一次读多少字节 -->  它的值应该是文件的大小，希望一次性将文件的内容读到内存中
    //获取文件的大小
    struct stat statbuff;  //获取文件的原数据信息
    fstat(fd,&statbuff);
    size_t size = statbuff.st_size; //获取到文件的大小
    cout << " size : " << size << endl;
    //char buff[size];   error
    //数组的大小必须在编译时确定，数组放在栈上，栈帧的大小应该在编译时运行
    //size 在运行时才知道
    char *buff = (char*)malloc(size);  //将数组放在堆上  ！！记得free
    assert(buff != NULL && "malloc failed");
    //设置回调函数
    // buff是值捕获，buff是局部指针变量，值捕获
    // 引用捕获，
    //！！！指针变量一律是值传递
    httptask->set_callback([buff](WFHttpTask *task)
    {
        //在httptask的回调函数中释放buff
        free(buff);  //不能直接访问到buff，需要捕获buff
    });

    WFFileIOTask *preadTask = WFTaskFactory::create_pread_task
    (
        //把fd、buff、size 传给后台框架，框架会把文件的内容读取到buff里
        fd,buff,size,0,
        bind(pread_callback,placeholders::_1,resp,filename)
    );

    // preadTask->start();  error
    // 会和heeptask并发执行，需要将preadtask追加到httptask的序列中
    //将preadtask放在serieswork序列中，在httptask前
    series_of(httptask)->push_back(preadTask);
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
