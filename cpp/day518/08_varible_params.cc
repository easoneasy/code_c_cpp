#include <iostream>

using namespace std;

//可变参数模板：适用于模板参数的个数不确定，类型不确定
//语法：template<typename ...Args>
//void func(Args ...args)  
//{
//
//}
// 把Args当作一个类型容器，可以装类型参数，K、T、U...
// args当作一个容器，装函数的所有的参数，K k、T t、U u...
// ...Args ： 表示打包，模板参数包，把类型参数打包在一起
// ...args ： 表示打包，函数参数包，把函数参数打包在一起
// Args... ： 解包，把类型参数包取出来
// args... ： 解包，把函数参数包取出来

//使用可用参数模板，一般情况下需要使用递归操作
//1、递归体：依次从包里逐个拿出数据
//2、递归出口：一般情况下定义一个普通函数作为递归出口

template<typename ...Args>
void print(Args ...args)
{
    //获取的函数参数包的 参数的个数
    cout << sizeof...(args) << endl;
    //获取模板参数包的 参数的个数
    cout << sizeof...(Args) <<endl;
}
void test1()
{
    print();
    print(1);
    print(1,3.14);
    print(1,3.14,"abc");
    //<T1,T2,T3,T4>
    //print<int,double,const char*,int>
    //参数类型是一样的，不会认为类型参数是同一个
    //会把参数当作新类型对待
    print(1,3.14,"abc",1);
}

//需求：打印可变参数模板中的所有数据
void show()
{
    cout << endl;
}

template<typename First,typename ...Args>
void show(First first,Args ...args)
{
    //递归体
    //先处理第一个数据
    cout << first << " ";
    //再处理剩余数据
    //递归调用
    show(args...); //解包
    
    //首先执行cout操作打印1 (first)
    //show(3.14,"abc",100)
    //3.14作为first，打印出来
    //show("abc",100);
    //"abc"作为first，打印
    //show(100);
    //100作为first,打印
    //show();
    //普通函数相比模板函数优先级高，会成为递归出口
}
void test2()
{
    show(1,3.14,"abc",100);
}

int main(int argc,char *argv[])
{
    // test1();
    test2();
    return 0;
}

