#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

/*
    bind：包装可调用对象，生成一个新的可调用对象，像函数一样调用
    可以改变函数形态，二元--- > 一元 ---> 零元
*/

int add(int a,int b)
{
    cout << "a : " << a << "  b : " << b << endl;
    return a + b;
}

//bind普通函数
void test1()
{
    add(1,2);
    cout << "-------------" << endl;
    //固定add的参数(1,2) int(int,int)
    auto f1 = bind(add,1,2);
    f1();
    cout << "-------------" << endl;
    //placeholders::_1 占位符 ，表示第一个参数
    //placeholders::_2 占位符 ，表示第二个参数
    //取值取决于实际的参数顺序
    auto f2 = bind(add,placeholders::_1,placeholders::_2);
    f2(100,200);
    cout << "-------------" << endl;
    auto f3 = bind(add,placeholders::_2,placeholders::_1);
    f3(200,100);  //a = 100, b=200
    cout << "-------------" << endl;
    //二元 --> 一元  函数的形式 ：int(int)
    auto f4 = bind(add,placeholders::_1,10);
    f4(100);

}

//bind包装函数对象
struct Callable
{
    int operator()(int a ,int b)
    {
        cout << " a = " << a << "  b = " << b << endl;
        return a+b;
    }
};

void test3()
{
    Callable callable;
    callable(1,2);
    cout << "-------------" << endl;
    auto f1 = bind(Callable(),1,2);
    f1();

    cout << "-------------" << endl;
    auto f2 = bind(Callable(),placeholders::_1,placeholders::_2);
    f2(100,200);

    cout << "-------------" << endl;
    auto f3 = bind(Callable(),placeholders::_1,20);
    f3(100);

}

//bind包装lambda
void test4()
{
    //直接调用1、2
    [](int a,int b)->void{
        cout << " a : " << a << "  b : " << b << endl;
    }(1,2);

    cout << "-------------" << endl;

    //auto接收lambda表达式再调用
    //void(int,int)
    auto f0 = [](int a ,int b)->void{
        cout << "a : " << a << "  b : " << b << endl;
    };
    f0(1,2);

    cout << "-------------" << endl;

    //bind绑定,二元-->零元
    auto f1 = bind([](int a, int b)->void{
        cout << " a : " << a << " b : " << b << endl;
    },1,2);
    f1();

    cout << "-------------" << endl;
    //bind绑定，二元-->一元
    auto f2 = bind([](int a,int b)->void{
        cout << "a : " << a << "  b : " << b << endl;
    },placeholders::_1,2);
    f2(1);

}

//bind包装成员函数
class MyClass
{
public:
    int add(int a,int b)
    {
        cout << "a : " << a << "  b: " << b << endl;
        return a+b;
    }
};

void test5()
{
    MyClass obj;
    obj.add(1,2);

    cout << "-------------" << endl;

    MyClass *p = &obj;
    p->add(1,2);

    cout << "-------------" << endl;

    auto f1 = bind(&MyClass::add,obj,10,20);
    f1();

    cout << "-------------" << endl;

    auto f2 = bind(&MyClass::add,&obj,1,2);
    f2();

    cout << "-------------" << endl;

    auto f3 = bind(&MyClass::add,&obj,placeholders::_1,100);
    f3(200);

    cout << "-------------" << endl;

    auto f4 = bind(&MyClass::add,&obj,placeholders::_1,placeholders::_2);
    f4(4,4);
}

//函数引用
void test6()
{
    int num = 1;
    int &ref = num;
    ref = 2;
    cout << ref << endl;
    cout << num << endl;

    cout << "-------------" << endl;

    int(&refAdd)(int,int)=add;
    //函数引用调用
    refAdd(1,2);

    cout << "-------------" << endl;

    auto &refAdd2 = add;
    //函数引用调用
    refAdd2(3,4);

    
}

int main(int argc,char *argv[])
{

    // test1();
    // test4();
    // test5();
    test6();

    return 0;
}

