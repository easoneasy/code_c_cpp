#include <iostream>
#include <functional>
using namespace std;

/*
    能否使用函数指针接收bind的返回结果

    function是通用多态函数包装器


*/

int func(int a ,int b)
{
    cout << " a : " << a << "  b : " << b << endl;
    return a+b;
}

void test1()
{
    func(1,2);
    cout << "----------------" << endl;
    using F = int(*)(int,int);
    F f = func;    //f是函数指针
    f(1,2);
    cout << "----------------" << endl;
    int (*f1)(int,int) =&func;   //函数指针指向func函数
    f1(3,4);

    auto f2 = bind(func,10,20);
    f2();
    cout << "----------------" << endl;
    // f1 = bind(func,100,200);   //bind的返回结果是一个可调用对象，可以像对象一样调用
    //---------所以不能用函数指针接收bind的结果
    //函数指针只能接收同类型的函数，bind的返回结果是一个函数对象，不是函数指针
}

void test2()
{
    //要保持函数的签名一致，返回值、形参一致
    function<int(int,int)> f3 = func;
    f3(1,2);
    //参数固定成1、2，调用的时候就不用传参
    function<int()> f4 = bind(func,1,2);
    f4();
}

struct Callable
{
    //重载了函数对象
    void operator()(int a ,int b)
    {
        cout << "a : " << a << "    b : " << b << endl;
    }
};

void test3()
{
    //void (int,int) 函数类型
    function<void(int,int)> f1 = Callable();
    f1(1,2);

    //使用bind改变函数形态
    function<void(int)> f2= bind(Callable(),1,placeholders::_1);
    f2(100);
}

void test4()
{
    // void(int)  函数类型  
    function<void(int)>  f1 = [](int num)->void{
        cout << "lambda" << endl;
        cout << num << endl;
    };
    f1(100);
    cout << "----------------" << endl;
    function<void()> f2 = bind([](int num)->void{
        cout << "lambda" << endl;
        cout << num << endl;
    },200);
    f2();
}

class MyClass
{
public:
    //成员函数
    void func(int a,int b)
    {
        cout << " a : " << a << "   b : " << b << endl;
    }
};

//function存储成员函数
void test6()
{
    MyClass obj;
    obj.func(1,2);   //对象.成员函数
    cout << "----------------" << endl;
    MyClass *p = &obj;  //指针->成员函数
    p->func(3,4);
    cout << "----------------" << endl;

    //void (MyClass&,int,int)
    function<void(MyClass&,int,int)> f1 = &MyClass::func;
    f1(obj,10,20);
    cout << "----------------" << endl;
    //void (MyClass*,int,int)
    function<void(MyClass*,int,int)> f2 = &MyClass::func;
    f2(&obj,10,20);

    cout << "----------------" << endl;
    //使用bind改变形态
    //void(int,int)
    function<void(int,int)> f3 = bind(&MyClass::func,obj,placeholders::_1,placeholders::_2);
    f3(100,200);
}

int main(int argc,char *argv[])
{

    // test1();
    // test3();
    // test4();
    test6();

    return 0;
}

