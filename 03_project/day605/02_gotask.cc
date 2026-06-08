#include <my_header.h>
#include <iostream>
#include <workflow/WFFacilities.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>

using namespace std;

/* gotask适合用来做一些复杂的业务计算：推荐系统
 * 加密解密：JWT签名认证，SHA256
 * 压缩、解压
 * 图片处理
 * 日志分析
 * 搜索引擎
 * 批量数据处理
 */

void add(int a ,int b ,int &c)
{
    sleep(3);
    c = a+b;
    cout << "c = " << c << endl;
}

int main(int argc,char *argv[])
{

    // 1、创建WFGoTask
    int a = 3;
    int b = 4;
    int c = 0;
    WFGoTask *task = WFTaskFactory::create_go_task("q1",add,a,b,ref(c));
    task->set_callback([&c](WFGoTask*)
        {
            cout << "[callback] : c = " << c << endl;
        });

    // 2、启动任务
    WFFacilities::WaitGroup waitGroup(1);

    SeriesWork *series = Workflow::create_series_work(task,[&waitGroup](const SeriesWork*)
        {
            waitGroup.done();
        });

    series->start();

    // 3、主线程等待
    waitGroup.wait();
    cout << "main : c = " << c << endl;

    return 0;
}
