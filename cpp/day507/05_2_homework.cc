#include <iostream>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Category.hh>
using namespace std;
using namespace log4cpp;
void test1(){
    //创建输出器对象
    OstreamAppender *appender1 = new OstreamAppender("console",&cout);
    FileAppender *appender2 = new FileAppender("file","log.txt");
    RollingFileAppender *appender3 = new RollingFileAppender("roll","A.log",100,5);
    //创建格式化器对象
    PatternLayout *layout1 = new PatternLayout{};
    PatternLayout *layout2 = new PatternLayout{};
    PatternLayout *layout3 = new PatternLayout{};
    //给格式化器对象设置输出格式
    layout1->setConversionPattern("%d [%p] %c : %m%n");
    layout2->setConversionPattern("%d [%p] %c : %m%n");
    layout3->setConversionPattern("%d [%p] %c : %m%n");
    //绑定格式化器和输出器 1 to 1
    appender1->setLayout(layout1);
    appender2->setLayout(layout2);
    appender3->setLayout(layout3);

    //找根记录器
    Category &root = Category::getRoot();
    //获取子记录器
    Category & userModel = Category::getInstance("UserModel");
    //设置子记录器不继承根记录器的输出器
    userModel.setAdditivity(false);
    //设置根的优先级
    root.setPriority(Priority::INFO);
    //设置子记录器的优先级
    userModel.setPriority(Priority::INFO);
    //设置根的输出器
    root.addAppender(appender1);
    root.addAppender(appender3);
    //设置子记录器的输出器
    userModel.addAppender(appender2);
    //设置根输出的信息
    for(int i = 0 ;i <10; ++i)
    {
        string num = to_string(i);
        root.debug(num + "debug msg ..");
        root.info(num + "info msg ..");
        root.notice(num + "notice msg ..");
        root.warn(num + "warn msg ..");

    }
    //设置userModel的输出信息
    userModel.debug("debug msg ..");
    userModel.info("info msg ..");
    userModel.notice("notice msg ..");
    userModel.warn("warn msg ..");

    Category::shutdown();


}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

