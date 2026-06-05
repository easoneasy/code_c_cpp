#include <iostream>
#include <string.h>
using namespace std;
//堆上实例对象
//私有一个参数构造函数
//public static的gerInstance参数

class Logger
{
public:
    //静态成员函数
    static Logger * getInstance()
    {
        if(!m_pInstance)
        {
            m_pInstance = new Logger{};
        }
        return m_pInstance;
    }
    //静态方法销毁
    static void destroyInstance()
    {
        if(m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }
    //删除拷贝函数
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    void get_log(char *logtxt)
    {
        m_logtxt = new char[strlen(logtxt)+1]{};
        strcpy(m_logtxt , logtxt);
        cout << m_logtxt << endl;
    }
    //析构函数
    ~Logger()
    {
        cout << "~Logger" << endl;
        if(m_logtxt)
        {
            delete [] m_logtxt;
            m_logtxt = nullptr;
        }
    }
private:
    //私有构造函数
    Logger()
    {
        cout << "Logger()" << endl;
    }

    char *m_logtxt;
    //静态成员
    static Logger *m_pInstance;

};
//类外初始化静态成员
Logger *Logger::m_pInstance = nullptr;

int main(int argc,char *argv[])
{
    Logger::getInstance();

    Logger::getInstance()->get_log("hello");

    Logger::destroyInstance();

    return 0;
}

