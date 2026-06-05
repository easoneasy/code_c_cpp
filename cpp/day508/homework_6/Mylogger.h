#ifndef __MYLOGGER__HH__ 
#define __MYLOGGER__HH__

#include <log4cpp/Category.hh>
#include <string>
using namespace log4cpp;
using namespace std;

// 定义一个宏用于日志拼接
#define addPrefix(msg)(string("[") \
        .append(__FILE__).append(":")\
        .append(__func__).append(":")\
        .append(to_string(__LINE__)).append("]")\
        .append(msg)).c_str()

#define LogWarn(msg) Mylogger::getInstance()->warn(addPrefix(msg))
#define LogInfo(msg) Mylogger::getInstance()->info(addPrefix(msg))
#define LogError(msg) Mylogger::getInstance()->error(addPrefix(msg))
#define LogDebug(msg) Mylogger::getInstance()->debug(addPrefix(msg))
// 单例模式
class Mylogger
{
public:
    //静态方法获取实例
    static Mylogger * getInstance();
    //静态方法销毁实例
    static void destroyInstance();
    // 删除赋值 赋值
    Mylogger(const Mylogger &) = delete;
    Mylogger & operator=(const Mylogger &) = delete;
    // info
    void info(const char * msg);
    // warn
    void warn(const char * msg);
    void error(const char * msg);
    void debug(const char * msg);
private:
    Mylogger();
    ~Mylogger();
    static Mylogger * ms_instance;
    Category & m_category;
};

#endif
