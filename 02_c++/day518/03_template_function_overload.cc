#include <iostream>

using namespace std;

//普通函数和函数模板之间重载了
//普通函数的优先级更高，有普通函数可以避免使用模板生成函数，效率更高

//函数模板和函数模板之间的重载
//可以通过两种情况区分：
//  1、通过个数区分
//  2、通过位置区分
//怎么区分：    把具体的函数写出来

void print(int a)
{
    cout << "normal func" << endl;
    cout << a << endl;
}

template<typename T>
void print(T t)
{
    cout << "template func" << endl;
    cout << t << endl; 
}

template<typename T>
void print2(T t)
{
    cout << "template func  1" << endl;
    cout << t << endl; 
}
template<typename T,typename U>
void print2(T t1,U u1)
{
    cout << "template func   2" << endl;
    cout << t1 << "   " << u1<< endl; 
}
void test1()
{
    print(10);
    cout << "----------" << endl;
    print(10.0);
    cout << "----------" << endl;
}

void test2()
{
    //模板1
    print2<int>(100);
    //模板2，T->int，U是自动推导int
    print2<int>(100,200);
    //模板2，指定了T、U的类型
    print2<int,int>(100,200);
    print2(100,200.3);
}

template<typename T>
void print3(T t1,T t2)
{
    cout << "template func   1" << endl;
    cout << t1 << "   " << t2 << endl; 
}
template<typename T,typename U>
void print3(T t1,U u1)
{
    cout << "template func   2" << endl;
    cout << t1 << "   " << u1<< endl; 
}
void test3()
{
    //模板1
    print3(1,2);
    print3<int>(1,2);
    //模板2
    print3<int,int>(1,2);
}

template<typename T,typename U>
T print4(T t,U u)
{
    cout << "template func   1" << endl;
    cout << t << "   " << u << endl; 
}
template<typename T,typename U>
T print4(U u, T t)
{
    cout << "template func   2" << endl;
    cout << u << "   " << t << endl; 
}
//先根据<>的类型和定义模板的类型匹配
//再根据()的传入实际参数的类型匹配
//不需要强制类型转换的优先级更高
void test4()
{
    // print(1,2);
    // print<int,int>(1,2);
    int x = 1;
    double y = 3.14;
    //模板1
    //T = int   U = double
    //int print4(int , double);
    //模板2
    //T = int  U = double
    //int print4(double , int);
    //模板1和模板2参数列表顺序不同，构成了函数重载
    print4<int,double>(x,y);  //模板1

    //模板1：
    //T = double U = int
    //double print4(double,int)
    //模板2
    //T = double U = int
    //double print4(int,double)
    print4<double,int>(x,y);  //模板2

}
int main(int argc,char *argv[])
{
    // test1();
    // test2();
    // test3();
    test4();

    return 0;
}

