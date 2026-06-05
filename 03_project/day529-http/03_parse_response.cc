#include <iostream>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFGlobal.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>

using namespace std;
using namespace protocol;

void http_callback(WFHttpTask *task)
{
    int state = task->get_state();
    //1、判断任务是否成功
    //WFT_STATE_SUCCESS 表示DNS成功、TCP成功、HTTP成功
    if(state != WFT_STATE_SUCCESS)
    {
        //打印错误信息
        cerr << WFGlobal::get_error_string(state,task->get_error()) << endl;
        return;
    }
    // 2、任务成功（收到http响应）
    //获取响应对象
    HttpResponse *resp = task->get_resp();
    cout << resp->get_http_version() << " "
         << resp->get_status_code() << " "
         <<resp->get_reason_phrase() << "\r\n";
    //解析响应头
    HttpHeaderCursor cursor(resp);
    string name;
    string value;
    while(cursor.next(name,value))
    {
        //解析头部成功
        cout << name << " : " << value << "\r\n";
    }
    cout << "\r\n";
    //获取响应体
    const void* body;
    //body的类型是void* 如果直接给cout，会认为想要打印地址
    size_t size;
    resp->get_parsed_body(&body,&size);
    cout << static_cast<const char*>(body) << endl;
    //将body从void* 转换成 char* cout会将body当成C字符串处理
    cout << "Task done " << endl;
}

void test1()
{
    //创建http任务
    WFHttpTask *task = WFTaskFactory::create_http_task(
        "http://www.baidu.com",
        3,
        3,
        http_callback
    );
    //2、设置参数
    HttpRequest * req = task->get_req();
    req->set_method("GET");
    req->set_request_uri("/");
    // 3、提交任务，让线程池异步执行任务
    //把任务提交给workflow调度器
    task->start();
    cout << "任务已提交" << endl;
    //让主线程阻塞，等待子线程的执行
    getchar();
    
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

