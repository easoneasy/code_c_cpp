#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

/*
    lambda表达式
        本质：匿名的函数对象，可以像函数一样调用
        允许在作用点/函数参数传递的位置定义一个临时、可调用的函数对象
        定义在局部的函数，是一种语法糖，简化了函数对象的定义
        []()opt->{}   opt：函数选项，一般不用
        [] 捕获列表
            获取lambda表达式同一作用域内的局部变量
            [&] ： 按引用捕获
            [=] ： 按值捕获
        ()参数列表
            像函数的参数列表一样
        ->返回值类型

        {} 函数体
            lambda表达式要执行的操作

*/

void func()
{
    cout << "func" << endl;
}

//基本语法使用
void test1()
{
    //一次性的调用
    //无参无返回值
    []()->void{
        cout << "lambda1" << endl;
    }();  //最后这个小括号相当于参数列表 ,相当于func();

    cout << "-----------------" << endl;

    //有参无返回值
    [](int num)->void{
        cout << " lambda 2" << endl;
        cout << "num = " << num << endl;
    }(100);  //相当func(100);

    cout << "-----------------" << endl;

    //有参数有返回值
    int sum = [](int a,int b)->int{
        cout << " lambda 3" << endl;
        return a+b;
    }(10,20);   //相当于 int sum = func(10,20);
    cout << "sum = " << sum <<endl;

    cout << "-----------------" << endl;

    //有参数有返回值   //->int 返回值可以省略
    int sum2 = [](int a,int b){
        cout << " lambda 4" << endl;
        return a+b;
    }(10,20);   //相当于 int sum = func(10,20);
    cout << "sum2 = " << sum <<endl;

    cout << "-----------------" << endl;

    //捕获列表，访问同一作用域其他的局部变量
    int num1 = 10;
    int num2 = 20;
    [num1,num2]()->void{ 
        cout << "lambda5" << endl;
        cout << "num1 = " << num1 << endl;
        cout << "num2 = " << num2 << endl;
    }();
    
}

//捕获列表的规则
void test2()
{
    int a = 1;
    int b = 2;
    // & ： 按引用捕获
    [&]()->void{
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        ++a; ++b;
    }();
    //按引用捕获，修改了 a、b的值
    cout << "a = " << a << " b = " << b << endl;
}

//捕获列表的规则
void test3()
{
    int a = 1;
    int b = 2;
    // = ： 按值捕获
    [=]()->void{
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        // ++a; ++b;  error,不可以在表达式内修改a、b的值
        //不能修改副本的值 
    }();
    //按引用捕获，修改了 a、b的值
    cout << "a = " << a << " b = " << b << endl;
}

void test4()
{
    int a = 1;
    int b = 2;
    int c = 3;
    // a 是引用捕获，其他是值捕获
    [=,&a]()->void{
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        cout << "c = " << c << endl;
        ++a;
        // ++b; //error

    }();
    //按引用捕获，修改了 a、b的值
    cout << "a = " << a << " b = " << b << " c= " << c << endl;
}

//捕获列表的规则
void test5()
{
    int a = 1;
    int b = 2;
    // = ： 按值捕获
    //使用opt选项，mutable，可以在lambda表达式中修改按值捕获的值
    [=]()mutable->void{
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        ++a; ++b;  
        cout << "a = " << a << " b = " << b << endl;
    }();
    //只修改了a、b的副本
    cout << "a = " << a << " b = " << b << endl;
}

void test6()
{
    auto f = []()->void{
        cout << " lambda 6" << endl;
    };
    f();
    f();
    f();
    
    cout << "----------------------" << endl;

    auto f1 = [](const int &num)->void{
        cout << " num = " << num << endl;
    };
    f1(10);
    f1(11);
    f1(12);
}

int main(int argc,char *argv[])
{

    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    test6();

    return 0;
}

