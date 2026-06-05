#include <iostream>
using namespace std;

class Singleton
{
public:
    static Singleton *getInstance()
    {
        if(!m_pInstance)
        {
            m_pInstance = new Singleton{};
        }
        return m_pInstance;
    }
    //资源释放函数
    static void  destroyInstance()
    {
        if(m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }
    //删除复制类型的函数
    Singleton (const Singleton &) = delete;
    Singleton &operator=(const Singleton &) =delete;

private:
    Singleton()
    {
        cout << "Singleton" << endl;
    }
    static Singleton *m_pInstance;
};
Singleton *Singleton::m_pInstance = nullptr;

void test1(){
    cout << Singleton::getInstance() << endl;
}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

