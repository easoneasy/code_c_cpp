#include <iostream>
#include <string.h>
#include <memory>
using namespace std;

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

//unique_ptr独占问题
void test1()
{
    //将原始指针暴露
    //分别交给了两个不同的unique_ptr管理
    Computer *p = new Computer{"xiaomi",1999};
    unique_ptr<Computer> up1 {p};
    unique_ptr<Computer> up2 {p};

    up1->print();
    up2->print();
}

//shared_ptr
void test2()
{
    //将原生指针初始化了两个独立的shared_ptr，造成了double free
    Computer *p = new Computer{"xiaomi",1999};
    shared_ptr<Computer> sp1{p};
    shared_ptr<Computer> sp2{p};
    cout << sp1.use_count() << endl;
    cout << sp1.use_count() << endl;
}

//循环引用
//两个类内部各自持有指向对方的shared_ptr，并且在堆上互相指向
//栈上的指针在程序生命周期结束时被销毁，而内部的引用计数依旧为1
//导致资源永远无法释放，造成内存泄漏
class childPtr;
class parentPtr
{
public:
    // shared_ptr<childPtr> child;
    weak_ptr<childPtr> child;

};
class childPtr
{
public:
    shared_ptr<parentPtr> parent;

};

void test3()
{
    shared_ptr<parentPtr> pp {new parentPtr{}};
    shared_ptr<childPtr> cp {new childPtr{}};
    cout << "pp.usecount :  " << pp.use_count() << endl;
    cout << "cp.usecount :  " << cp.use_count() << endl;
    cout << "-------------" << endl;
    //将内部指针指向另一个对象
    pp->child = cp;
    cp->parent = pp;
    cout << "pp.usecount :  " << pp.use_count() << endl;
    cout << "cp.usecount :  " << cp.use_count() << endl;

}
int main(int argc,char *argv[])
{

    // test1();
    // test2();
    test3();

    return 0;
}

