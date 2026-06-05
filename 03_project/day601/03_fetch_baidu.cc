#include <iostream>
#include <workflow/HttpMessage.h>
#include <workflow/WFFacilities.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFGlobal.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>

using namespace std;
using namespace protocol;
// 等待组：原子变量 + 条件变量（等待唤醒机制）
WFFacilities::WaitGroup waitGroup(1);

void http_callback(WFHttpTask *task)
{
    // 1、检查任务的状态
    int state = task->get_state();
    if(state != WFT_STATE_SUCCESS)
    {
        cerr << WFGlobal::get_error_string(state,task->get_error()) << endl;
        // 将waitGroup的值 减1
        waitGroup.done();
        return;
    }
    // 2、打印百度的首页
    HttpResponse *resp = task->get_resp();
    // a. 响应行
    cout << resp->get_http_version() << " "
        << resp->get_status_code() << " "
        << resp->get_reason_phrase() << "\r\n";
    // b. 响应头部
    HttpHeaderCursor cursor(resp);
    string name;
    string value;
    while(cursor.next(name,value))
    {
        cout << name << " : " << value << "\r\n";
    }
    cout << "\r\n";

    // c.响应体
    const void* body;
    size_t size;
    resp->get_parsed_body(&body,&size);
    cout << static_cast<const char*>(body) << endl;
    //waitGroup的值 减1
    waitGroup.done();
}

void test1()
{
    // 1、创建HTTP任务
    WFHttpTask *task = WFTaskFactory::create_http_task
    (
        "http://www.baidu.com",
        3,3,
        http_callback  //设置回调函数，任务执行完后才会执行回调函数
    );
    // 2、设置任务参数
    HttpRequest *req = task->get_req();
    req->set_method("GET");
    //设置请求头部
    req->set_header_pair("User-Agent","WorkflowHttpClient");
    //请求结束之后关闭TCP连接
    req->set_header_pair("Connection","close");
    // 3、启动任务，交给框架异步执行
    task->start();
    // 让当前线程阻塞，直到waitGroup的值为0
    waitGroup.wait();
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

