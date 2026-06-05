#include <iostream>
using namespace std;

class Singleton
{
public:
    static Singleton *getInstance()
    {
        //如果m_pInstance不存在
        if(!m_pInstance)
        {
            m_pInstance = new Singleton{};
            
        }
        return m_pInstance;
    }
    //资源清理函数
    static void destroyInstance()
    {
        if(m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

private:
    //删除拷贝型函数
    Singleton(const Singleton & ) = delete;
    Singleton &operator=(const Singleton &) = delete;
    //构造函数
    Singleton()
    {
        cout << "Singleton" << endl;
    }
    //静态变量指针
    static Singleton *m_pInstance;
};
Singleton *Singleton::m_pInstance = nullptr;
void test1(){
    cout << Singleton::getInstance() << endl;
    Singleton::destroyInstance();
}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

