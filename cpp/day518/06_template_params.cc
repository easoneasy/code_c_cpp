#include <iostream>

using namespace std;

//模板的参数：
//  1、类型参数：T、K、U、V
//  2、非类型参数：一般是整数、小数

//模板参数也可以设置默认值

template<typename T,int N>
void print1(T t)
{
    cout << t * N << endl;
}

void test1()
{
    // 显实例化
    print1<int,10>(2);  //T : int; N = 10;

    // 隐式实例化
    // print1(3);     //error ,没有指定N的值
}

template<typename T,int N=10>
void print2(T t)
{
    cout << t * N << endl;
}

void test2()
{
    //隐式实例化
    print2(3);     //error ,没有指定N的值
    //显式实例化
    print2<double>(3.14);
    print2<double,100>(3.14);
}
int main(int argc,char *argv[])
{
    // test1();
    test2();
    return 0;
}

