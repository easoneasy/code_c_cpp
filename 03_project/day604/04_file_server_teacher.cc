
#include <my_header.h>
#include <iostream>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFGlobal.h>
#include <workflow/WFHttpServer.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>

using namespace std;
using namespace protocol;
using namespace std::placeholders;

WFFacilities::WaitGroup waitGroup(1);

void sig_handler(int)
{
    waitGroup.done();
}

void pread_callback(WFFileIOTask* task, HttpResponse* resp, string filename)
{
    // struct FileIOArgs
    // {
    // 	int fd;
    // 	void *buf;
    // 	size_t count;
    // 	off_t offset;
    // };
    // 1. 获取参数和返回值
    FileIOArgs* args = task->get_args();
    close(args->fd); // 千万不要忘记关闭文件描述符!
    long bytes = task->get_retval(); // 获取实际读取的字节数目
    // 2. 判断任务的状态
    int state = task->get_state();
    if (state != WFT_STATE_SUCCESS) {
        cerr << WFGlobal::get_error_string(state, task->get_error()) << endl;
        resp->set_status_code("500");
        resp->append_output_body("<html>500 Server Internal Error.</html>");
        return;
    }
    // 3. 将文件内容(buf)追加到响应体中
    // 慎重使用'_nocopy'：保证args->buf的生命周期长于HttpTask
    resp->add_header_pair("Content-Disposition", "attachment; filename=" + filename);
    resp->append_output_body_nocopy(args->buf, bytes);
}

void process(WFHttpTask* httpTask)
{
    // GET /dir/a.txt HTTP/1.1
    // 1. 解析请求
    HttpRequest* req = httpTask->get_req();
    string uri = req->get_request_uri();
    auto pos = uri.find('?');
    string path = uri.substr(0, pos);
    // cout << "[path] " << path << endl;
    // 路径映射
    if (path == "/") {
        path += "index.html";
    }
    path = "resources" + path;
    cout << "[path] " << path << endl;
    // 获取文件名
    pos = path.find_last_of('/');
    string filename = path.substr(pos + 1);
    cout << "[filename] " << filename << endl;

    // 2. 创建pread任务
    HttpResponse* resp = httpTask->get_resp();
    resp->add_header_pair("Server", "Sogou C++ Workflow Server");

    int fd = open(path.c_str(), O_RDONLY);
    if (fd == -1) {
        resp->set_status_code("404");
        resp->append_output_body("<html>404 Not Found.</html>");
        return;
    }
    // 获取文件的大小
    struct stat statbuf;
    fstat(fd, &statbuf);
    size_t size = statbuf.st_size;
    cout << "size: " << size << endl;

    char* buf = (char*)malloc(size); // buf:指针变量，局部变量
    assert(buf != NULL && "malloc failed");

    // 原则：指针变量一律值传递！
    httpTask->set_callback([buf](WFHttpTask* task) {
        free(buf); // 在httpTask的回调函数中释放buf
    });

    WFFileIOTask* preadTask = WFTaskFactory::create_pread_task(
        fd,
        buf,
        size,
        0,
        std::bind(pread_callback, _1, resp, filename));

    // 3. 将preadTask添加到序列中
    // preadTask->start(); // ERROR: preadTask回合httpTask并发执行
    series_of(httpTask)->push_back(preadTask);
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
