#include <iostream>
#include <openssl/ssl.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>

using namespace std;

// 序列1 和 序列2 并发执行
// 序列里面的任务是按序执行

int main(int argc,char *argv[])
{

    // 1、创建序列1
    WFGoTask *task1 = WFTaskFactory::create_go_task("task",[]()
        {
            cout << "series1 : task1 done" << endl;
        });
    WFGoTask *task2 = WFTaskFactory::create_go_task("task",[]()
            {
                cout << "series1 : task2 done" << endl;
            });
    WFGoTask *task3 = WFTaskFactory::create_go_task("task",[]()
            {
                cout << "series1 : task3 done" << endl;
            });
    SeriesWork *series1 = Workflow::create_series_work(task1,[](const SeriesWork*)
        {
            cout << "series1 completes" << endl;
        });
    // series1->push_back(task2);
    // series1->push_back(task3);
    // 重载了 << 运算符
    *series1 << task2 << task3;


    // 2、创建序列2
    WFGoTask *job1 = WFTaskFactory::create_go_task("job",[]()
        {
            cout << "series2 : job1 done" << endl;
        });
    WFGoTask *job2 = WFTaskFactory::create_go_task("job",[]()
            {
                cout << "series2 : job2 done" << endl;
            });
    WFGoTask *job3 = WFTaskFactory::create_go_task("job",[]()
            {
                cout << "series2 : job3 done" << endl;
            });
    SeriesWork *series2 = Workflow::create_series_work(job1,[](const SeriesWork*)
        {
            cout << "series2 completes" << endl;
        });
    // series1->push_back(task2);
    // series1->push_back(task3);
    // 重载了 << 运算符
    *series2 << job2 << job3;
    // 3、将两个序列添加到parallelWork中
    WFFacilities::WaitGroup waitGroup(1);
    ParallelWork *parallel = Workflow::create_parallel_work([&waitGroup](const ParallelWork*)
        {
            cout << "ParallelWork done!" << endl;
            waitGroup.done();
        });

    parallel->add_series(series1);
    parallel->add_series(series2);

    // 4、启动ParallelWork
    parallel->start();
    // 5、主线程阻塞等待子线程执行
    waitGroup.wait();
    cout << "主线程退出" << endl;
    return 0;
}
