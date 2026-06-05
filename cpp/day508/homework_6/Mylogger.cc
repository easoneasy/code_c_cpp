#include"Mylogger.h"
#include<log4cpp/Priority.hh>
#include<log4cpp/OstreamAppender.hh>
#include<log4cpp/FileAppender.hh>
#include<log4cpp/PatternLayout.hh>
#include <iostream>

//初始化静态指针
Mylogger *Mylogger::ms_instance = nullptr;

//创建对象
Mylogger *Mylogger::getInstance()
{
    if(!ms_instance)
    {
        ms_instance = new Mylogger{};
    }
    return ms_instance;
}

//销毁资源
void Mylogger::destroyInstance()
{
    if(ms_instance)
    {
        delete ms_instance;
        ms_instance = nullptr;
    }
}

//实现构造函数
Mylogger::Mylogger()
//绑定到单例对象
:m_category(Category::getRoot().getInstance("MyCat"))
{
    OstreamAppender *appender1 = new OstreamAppender("console",&cout);
    FileAppender *appender2 = new FileAppender("file","log.txt");

    PatternLayout *layout1 = new PatternLayout{};
    PatternLayout *layout2 = new PatternLayout{};

    layout1->setConversionPattern("%d [%p] %m%n");
    layout2->setConversionPattern("%d [%p] %m%n");

    appender1->setLayout(layout1);
    appender2->setLayout(layout2);

    m_category.setPriority(Priority::DEBUG);
    m_category.addAppender(appender1);
    m_category.addAppender(appender2);

}

Mylogger::~Mylogger()
{
    Category::shutdown();
}

void Mylogger::info(const char *msg)
{
    m_category.info(msg);
}
void Mylogger::warn(const char *msg)
{
    m_category.warn(msg);
}
void Mylogger::error(const char *msg)
{
    m_category.error(msg);
}
void Mylogger::debug(const char *msg)
{
    m_category.debug(msg);
}
