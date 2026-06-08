#include <cstddef>
#include <iostream>
#include <workflow/WFFacilities.h>
#include <workflow/WFGraphTask.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>

/*
 *    timer(a)
        |
 ┌──────┴──────┐
 |             |
 ▼            ▼
http1(b)     http2(c)
 |             |
 └──────┬──────┘
        ▼
    display(d)
 *
 */

using namespace std;

void http_callback(WFHttpTask *httptask)
{
    int state = httptask->get_state();
    if(state != WFT_STATE_SUCCESS)
    {
        return;
    }
    const void *body;
    size_t *size = static_cast<size_t*>(httptask->user_data);
    httptask->get_resp()->get_parsed_body(&body, size);
}

int main(int argc,char *argv[])
{
    // 1、创建4个任务
    WFTimerTask *timer = WFTaskFactory::create_timer_task(1,0,[](WFTimerTask*)
        {
            cout << "Timer task complete" << endl;
        });
    WFHttpTask *http1 = WFTaskFactory::create_http_task("http://www.baidu.com",3,3,http_callback);
    size_t size1;
    http1->user_data=&size1;

    WFHttpTask *http2 = WFTaskFactory::create_http_task("http://www.sogou.com",3,3,http_callback);
    size_t size2;
    http2->user_data=&size2;

    // 相当于汇聚结点，为了等待http1、http2执行完毕，再执行后续的逻辑
    // 这个结点通常来汇总计算，整合两个/多个的执行结果
    // 例如：http1 获取用户信息，http2获取订单信息
    // 在display这里进行汇总计算，合并两个请求的结果，最后返回结果
    WFGoTask *display = WFTaskFactory::create_go_task("q1",[&]()
        {
            cout << "百度首页的大小：" << size1 << endl;
            cout << "搜狗首页的大小:" << size2 << endl;
         });

    // 2、构建DAG图任务
    // 空图，没有任何结点
    WFGraphTask *graph = WFTaskFactory::create_graph_task([](WFGraphTask *)
        {
            cout << "DAG图任务完成"<< endl;
        });

    // 向图任务中添加结点  (四个孤立的结点，没有依赖关系，直接启动会并发执行)
    // 将timer添加到graph中，变成graph的一个结点
    // 设计模式：Wrapper（装饰者模式/包装器模式）
    WFGraphNode &a = graph->create_graph_node(timer);
    WFGraphNode &b = graph->create_graph_node(http1);
    WFGraphNode &c = graph->create_graph_node(http2);
    WFGraphNode &d = graph->create_graph_node(display);

    // 定义结点之间的依赖关系
    // (运算符重载) '--' +  '>' / '<'
    a --> b;
    b --> d;
    a --> c;
    c --> d;

    // 3、启动DAG图任务（拓扑排序）
    WFFacilities::WaitGroup waitGroup(1);
    SeriesWork * series = Workflow::create_series_work(graph,[&waitGroup](const SeriesWork*)
        {
            waitGroup.done();
        });
    series->start();
    // 4、主线程等待图任务结束
    waitGroup.wait();

    return 0;
}
