#include <iostream>

using namespace std;

//把模板作用在函数上：函数模板

//基本语法：
//  template<typename/class T,typename U,typename K....>
//template关键字，一定要加
//T、U、K 是模板参数/类型参数，表示一种通用类型，使用什么无所谓，占位作用。
//          尽量不要使用像XYZ这样的命名
//          具体取决于传入的类型是什么
// T : type
// K : key
// V : value
// E : element

//把模板作用在函数上
//函数的声明和实现写在一起
//编译器会根据模板生成具体的函数
template<typename T>
void print(T t)
{
    cout << "print(T)" << endl;
    cout << t << endl;
}

//函数声明和实现分开写
//函数声明
template<typename T>
//R类型是返回值，T类型是参数类型
void print2(T t);

//函数实现
//还需要定义模板template
template<typename T>
void print2(T t)
{
    cout << "print2()" <<endl;
    cout << t << endl;
}

void test1()
{
    //显式实例化，指明具体类型
    print<int>(2);
    print<double>(3.14);
    cout << "------------"<< endl;
    //隐式实例化
    print(200);
    print(200.222);
    cout << "------------"<< endl;
    print2(1);

}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

