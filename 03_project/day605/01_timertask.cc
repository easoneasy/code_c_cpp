#include <my_header.h>
#include <iostream>
#include <workflow/WFFacilities.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>

using namespace std;

void timer_callback(WFTimerTask *task)
{
    // 获取任务的状态
    int state = task->get_state();
    if(state != WFT_STATE_SUCCESS)
    {
        cout << "Timer Canceled!" << endl;
        return;
    }
    cout << "Timer Triggered" << endl;
    // 设置新的定时器，1秒触发一次，回调函数就是本函数，相当于自我调用（循环）
    // 直到task的任务状态不为WFT_STATE_SUCCESS
    WFTimerTask *next = WFTaskFactory::create_timer_task("timer",1,0,timer_callback);
    // 将新建的定时器放入task的序列中
    // 只要没到10秒就间隔1秒生成一个定时器再将定时器放入序列中
    series_of(task)->push_back(next);
}

int main(int argc,char *argv[])
{
    // 1、创建有名定时器任务
    WFTimerTask *task = WFTaskFactory::create_timer_task
        (
            "timer",3,0,timer_callback
        );
    // 2、启动定时器任务
    WFFacilities::WaitGroup waitGroup(1);

    // 将task任务添加到序列中，设置序列的回调函数
    // 回调函数是一个lambda表达式，当序列中的任务全部结束时会执行这个lambda表达式
    // 将计数器设置为0，注意要使用引用
    SeriesWork *series = Workflow::create_series_work(task,[&waitGroup](const SeriesWork*)
        {
            waitGroup.done();
        });
    // 启动序列
    series->start();

    // 3、主线程等待
    sleep(10);

    // 主线程sleep10秒之后，取消所有叫timer的计时器
    WFTaskFactory::cancel_by_name("timer");

    waitGroup.wait();

    return 0;
}
