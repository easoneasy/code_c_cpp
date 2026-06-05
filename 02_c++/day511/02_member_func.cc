#include <iostream>
using namespace std;

void func1()
{
    cout <<"func1" << endl;
}
void func2()
{
    cout <<"func2" << endl;
}
void func3()
{
    cout <<"func3" << endl;
}

void test1(){
    func1();
    cout << "------------"<< endl;
    //简写
    void (*f)()=func1;
    f();
    cout << "------------"<< endl;
    //完整
    f = &func2;
    (*f)();
    cout << "------------"<< endl;
    //定义别名
    typedef void (*F)();
    F ff = &func1;
    ff();
    cout << "------------"<< endl;
    //using 别名=类型
    using FFF = void(*)();
    FFF fff = &func3;
    fff();
}

class FFF
{
public:
    void f1()
    {
        cout << "FFF::f1()" << endl;
    }
    void f2()
    {
        cout << "FFF::f2()" << endl;
    }
    void f3()
    {
        cout << "FFF::f3()" << endl;
        cout << "m_data" << m_data << endl;
    }
private:
    int m_data = 1;
};
void test2()
{
    FFF obj;
    obj.f3();
    cout << "------------" << endl;
    FFF *p = &obj;
    p->f3();
    cout << "------------" << endl;
    void (FFF::*f)() = &FFF::f1;
    (obj.*f)();
    (p->*f)();
}

int main(int argc,char *argv[])
{
    /* test1(); */
    test2();
    return 0;
}

