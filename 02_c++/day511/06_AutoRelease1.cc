#include <iostream>
using namespace std;

//静态单例
class Singleton
{
public:
    //提供静态函数，返回唯一对象
    static Singleton *getInstance()
    {
        if(!m_pInstance)
        {
            m_pInstance = new Singleton{};
        }
        return m_pInstance;
    }
    /* //资源清理函数 */
    /* static Singleton destroyInstance() */
    /* { */
    /*     if(m_pInstance) */
    /*     { */
    /*         delete m_pInstance; */
    /*         m_pInstance = nullptr; */
    /*     } */
    /* } */
    //删除复制控制相关函数
    Singleton(const Singleton &)=delete;
    Singleton &operator=(const Singleton &)=delete;
    //把管理者类设置成友元函数
    friend class AutoRelease;

private:
    Singleton()
    {
        cout << "Singleton()"<< endl;
    }
    ~Singleton()
    {
        cout << "~Singleton" << endl;
    }
    static Singleton *m_pInstance;
};
//在外部初始化静态成员
Singleton *Singleton::m_pInstance = nullptr;

//管理者类
class AutoRelease
{
public:
    AutoRelease(Singleton *p)
    :m_p(p)
    {
        cout << "AutoRelease(Singleton)" << endl;
    }
    ~AutoRelease()
    {
        cout << "~AutoRelease" << endl;
        if(m_p)
        {
            delete m_p;
            m_p = nullptr;
        }
    }
private:
    //资源类型的指针，指向所管理资源
    Singleton *m_p;
};
void test1(){
    AutoRelease ar{Singleton::getInstance()};
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

