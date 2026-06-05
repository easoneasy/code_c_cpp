#include <iostream>
#include <functional>
using namespace std;

/*
    ref ---> 引用包装器
*/

void func(int a, int &b, const int c)
{
    a++;
    b++;
    // c++; //error
    cout << "a : " << a << " b : " << b << " c : " << c << endl;
}

void test1()
{
    int a = 1;
    int b = 2;
    int c = 3;
    cout << "a : " << a << " b : " << b << " c : " << c << endl;
    // bind的传值方式默认为值传递
    //修改传值方式  值传递--->引用传递
    //使用引用包装器  ref  \  cref
    // auto f = bind(func, a, b, c);   // f是新的可调用对象
    //b的传值方式 ： 值传递 ---> 引用传递
    auto f = bind(func, a, ref(b), c);   // f是新的可调用对象
    f();
    cout << "a : " << a << " b : " << b << " c : " << c << endl;
}

int main(int argc, char *argv[])
{

    test1();

    return 0;
}
