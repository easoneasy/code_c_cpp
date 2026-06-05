#include <iostream>
#include <string.h>
using namespace std;

template<typename T>
class RAII
{
public:
    //构造函数
    RAII(T *p)
    :m_p(p)
    {
        cout <<"init constructor" << endl;
    }
    //析构函数
    ~RAII()
    {
        if(m_p)
        {
            delete m_p;
            m_p = nullptr;
        }
    }
    //删除拷贝类型的函数
    RAII(const RAII &) = delete;
    RAII &operator=(const RAII &) = delete;
    //提供访问资源的函数
    T *operator->()
    {
        return m_p;
    }
    T &operator*()
    {
        return *m_p;
    }
    T *get()
    {
        return m_p;
    }
private:
    T *m_p;
};

class Computer
{
public:
    //构造函数
    Computer(const char* brand,int price)
    :m_brand(new char[strlen(brand)+1]{})
    ,m_price(price)
    {
        cout << "Computer constructor" << endl;
        strcpy(m_brand,brand);
    }
    //析构函数
    ~Computer()
    {
        if(m_brand)
        {
            delete [] m_brand;
            m_brand = nullptr;
        }
        cout << "~Computer" << endl;
    }
    //拷贝构造函数
    Computer(const Computer &rhs)
    :m_brand(new char[strlen(rhs.m_brand)+1]{})
    ,m_price(rhs.m_price)
    {
        cout << "Computer(const Computer &)" << endl;
        strcpy(m_brand,rhs.m_brand);
    }
    //赋值运算符函数
    Computer &operator=(const Computer &rhs)
    {
        if(this != &rhs)
        {
            delete [] m_brand;
            m_brand = new char[strlen(rhs.m_brand)+1]{};
            strcpy(m_brand,rhs.m_brand);

        }
        cout << "Computer &operator=" << endl;
        return *this;
    }
    void print()
    {
        cout << "品牌：" << m_brand << "价格：" <<m_price << endl;
    }
private:
    char *m_brand;
    int m_price;
};

void test1()
{
    RAII raii {new Computer{"xiaomi",1999}};
    raii->print();
    (*raii).print(); 
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

