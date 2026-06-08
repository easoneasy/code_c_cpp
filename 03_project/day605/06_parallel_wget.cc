#include <iostream>
#include <openssl/ssl.h>
#include <workflow/HttpMessage.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFGlobal.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>

using namespace std;
using namespace protocol;
/*
 * ParallelWork
 │
 ├── Series1
 │     └── HttpTask(百度)
 │
 ├── Series2
 │     └── HttpTask(搜狗)
 │
 └── Series3
       └── HttpTask(QQ)
 */

// 并行抓取网页，按序输出
// 并行：多个序列，一个series一个task
// 按序输出：根据用户输入的URI，
// parallelWork

// 存放http响应的结果
struct SeriesContex
{
    string url;
    int state;
    int error;
    // ！！！  resp 结构体 ， 不能是指针
    // task->get_resp()的返回结果是对象的地址
    // 如果是指针，在http回调函数结束之后对象就会被释放
    // 指针就会悬空，变成野指针
    // 后面执行parallel的回调函数时，执行ctx->resp可能会导致程序崩溃，发生段错误
    // 写成对象的原因是：把响应内容拷贝（移动）出来，保存到SeriesContex中
    // 即便task销毁，series的Contex中还有一份
    HttpResponse resp;
};

// 保存Http的执行结果，放入seriesContex结构体中
// 获取到命令行输入的网址的结果之后再统一由parallel输出
void http_callback(WFHttpTask *task)
{
    // 通过task找到回调函数所属的series
    // task没有自己的Context，只能通过series获取Contex
    // 因为Contex放在series上，所以要知道自己在哪里
    SeriesWork *series = series_of(task);
    // 获取上下文
    // 每个series都有自己的SeriesContex
    // series->get_contex() 拿到的是这个http任务对应的结果存储区
    SeriesContex *ctx = static_cast<SeriesContex*>(series->get_context());
    ctx->state = task->get_state();
    ctx->error = task->get_error();
    // 结构体不能放resp的指针
    // HttpResponse *resp 指针 是 task->get_resp() 的返回结果
    // ctx->resp 是HttpResponse对象， 类型不匹配，需要解引用
    // std::move 调用移动运算符函数，将资源的所有权转移给resp，而不是直接复制
    // （数据内容可能会很多，移动运算符函数开销较小）
    ctx->resp = std::move(*(task->get_resp()));
}

// 按用户输入的URI顺序输出网页信息
// parallel的回调函数只负责从seriesContex中取结果并输入结果
// 不需要再访问网络
void parallel_callback(const ParallelWork *parallel)
{
    for(int i = 0 ; i< parallel->size() ; ++i )
    {
        // 获取序列，按照series的加入顺序输出
        // 获取的是第i个加入parallel的series，而不是第i个完成任务的series
        const SeriesWork *series = parallel->series_at(i);
        // 获取序列的上下文
        SeriesContex *ctx = static_cast<SeriesContex*>(series->get_context());
        cout << ctx->url << " : " << endl;
        if(ctx->state != WFT_STATE_SUCCESS)
        {
            cout << WFGlobal::get_error_string(ctx->state, ctx->error) << endl;
        }else{
            // 获取网页的内容,并输出
            const void* body;
            size_t size;
            ctx->resp.get_parsed_body(&body, &size);
            cout << static_cast<const char*>(body);
        }
    }
}

int main(int argc,char *argv[])
{
    // 1、命令行参数校验 接受命令行参数
    if(argc < 2)
    {
        cerr << "Usage : " << argv[0] << "<URI>" << endl;
        exit(1);
    }

    // 2、根据用户输入的URI创建Http任务
    ParallelWork *parallel = Workflow::create_parallel_work(parallel_callback);
    for(int i = 1;i < argc;++i)
    {
        // 每个task放入序列中 ， 添加的顺序是用户输入URI的顺序
        WFHttpTask *task = WFTaskFactory::create_http_task(argv[i],3,3,http_callback);
        SeriesWork *series = Workflow::create_series_work(task,nullptr);

        // 设置序列的上下文
        SeriesContex *ctx = new SeriesContex;
        ctx->url = argv[1];
        series->set_context(ctx);

        // 把series添加到parallel中
        // 按用户输入的URI的顺序添加到seriesWork
        // parallelwork记录了series的顺序
        parallel->add_series(series);
    }

    // 3、启动parallelWork
    // 把parallelWork放在序列中启动
    WFFacilities::WaitGroup waitGroup(1);
    Workflow::start_series_work(parallel,[&waitGroup](const SeriesWork*)
        {
            waitGroup.done();
        });

    // 4、让主线程阻塞
    waitGroup.wait();

    return 0;
}
