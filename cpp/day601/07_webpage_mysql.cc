#include <iostream>
#include <string>
#include <workflow/HttpMessage.h>
#include <workflow/MySQLMessage.h>
#include <workflow/MySQLResult.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFGlobal.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>

using namespace std;
using namespace protocol;

struct SeriesContext
{
    string url;     //网页url
    size_t size;    //网页大小
    bool success;   //序列是否成功
};

void mysql_callback(WFMySQLTask *mysqlTask)
{
    // 1、判断任务的状态
    int state = mysqlTask->get_state();
    if(state != WFT_STATE_SUCCESS)
    {
        cerr << WFGlobal::get_error_string(state,mysqlTask->get_error()) << endl;
        return;
    }
    // 2、判断返回包的类型
    MySQLResponse *resp = mysqlTask->get_resp();
    if(resp->get_packet_type() == MYSQL_PACKET_ERROR)
    {
        cerr << resp->get_error_code() << " "
            << resp->get_error_msg() << endl;
        return;
    }
    // 3、解析结果集
    SeriesWork *series = series_of(mysqlTask);
    SeriesContext *ctx = static_cast<SeriesContext*>(series->get_context());
    ctx->success = true;
    MySQLResultCursor cursor(resp);
    cout << "插入记录： id = " << cursor.get_insert_id() << endl;
}

void http_callback(WFHttpTask *httptask)
{
    // 1、判断任务状态
    int state = httptask->get_state();
    if(state != WFT_STATE_SUCCESS)
    {
        cerr << WFGlobal::get_error_string(state,httptask->get_error()) << endl;
        return;
    }
    // 2、获取响应体
    SeriesWork *series = series_of(httptask);
    SeriesContext *ctx = static_cast<SeriesContext*>(series->get_context());

    HttpResponse *resp = httptask->get_resp();
    const void* body;
    size_t size;
    resp->get_parsed_body(&body,&size);
    ctx->size = size;

    // 3、创建MySQL任务
    WFMySQLTask *mysqlTask = WFTaskFactory::create_mysql_task
    (
        "mysql://root:123456@localhost:3306/demo",
        3,mysql_callback
    );
    
    // 4、设置MySQL任务的参数
    string url = static_cast<char*>(httptask->user_data);
    string sql = "insert into tbl_webpage(url,size) values('"+ url + "' , " + to_string(size) + " )";
    cout << "[SQL]" << sql << endl;

    // 5、将MySQL任务添加到序列中
    series->push_back(mysqlTask);
}

int main(int argc,char *argv[])
{
    // 1、校验命令行参数
    if(argc != 2)
    {
        cerr << "Usage : " << argv[0] << "<URL>" << endl;
        return 1;
    }

    // 2、创建HTTP任务
    WFHttpTask *httptask = WFTaskFactory::create_http_task
    (
        argv[1],
        3,3,
        http_callback
    );
    // task类的成员变量 void*类型
    // 把临时数据挂在任务身上，跟着任务到处跑
    // 只有在httptask这个任务上有效
    // 核心结论： 任何类型的指针都可以自动转换成void*，不需要手动类型转换
    httptask->user_data = argv[1];

    // 3、设置任务参数
    HttpRequest *req = httptask->get_req();
    req->add_header_pair("Accept","*/*");
    req->add_header_pair("User-Agent","wget/1.14 (linux-gnu)");
    req->add_header_pair("Connection","close");

    HttpResponse *resp = httptask->get_resp();
    resp->set_size_limit(20 * 1024 * 1024);  // 20M
    httptask->set_receive_timeout(30 * 1000); // 30s

    // 4、创建串行任务流： SeriesWork
    WFFacilities::WaitGroup waitGroup(1);

    //创建序列
    SeriesWork *series = Workflow::create_series_work(httptask,
        [&waitGroup](const SeriesWork* series)
        {
            //lambda表达式是整个seriesWork序列的总回调函数
            //当队列中所有的任务都按顺序执行完毕，或崩溃时，序列结束
            //结束的瞬间框架会自动调用这个 Lambda 表达式

            // 从series里把在外面new的对象地址拿出来，给ctx
            SeriesContext* ctx = static_cast<SeriesContext*>(series->get_context());
            //告诉控制台这次任务的结果
            if(ctx->success)
            {
                cout << " success " << endl;
            }else{
                cout << " failed " << endl;
            }
            //在这里释放堆上的对象
            delete ctx;
            waitGroup.done();
        });

        //设置序列的上下文
        SeriesContext *ctx = new SeriesContext{argv[1],0,false};

        series->set_context(ctx);

        series->start();

        // 5、主线程等待序列结束
        waitGroup.wait();

    return 0;
}

