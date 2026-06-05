#include <iostream>
using namespace std;

class Singleton
{
public:
    static Singleton *getInstance()
    {
        if(!m_pInstance){
            m_pInstance = new Singleton{};
        }
        return m_pInstance;
    }
    //释放资源
    static void destoryInstance()
    {
        if(m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

    //删除复制类型函数
    Singleton (const Singleton &) = delete;
    Singleton & operator = (const Singleton&) = delete;

private:
    Singleton(){}
    //增加一个自身类型的指针
    static Singleton *m_pInstance;
};
//类外初始化
Singleton *Singleton::m_pInstance=nullptr;
void test1(){
    cout << Singleton::getInstance() << endl;
}

int main(int argc,char *argv[])
{
    test1();



    return 0;
}

