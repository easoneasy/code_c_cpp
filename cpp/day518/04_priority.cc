#include <iostream>

using namespace std;

//匹配优先级的问题：
//1.普通函数和模板函数之间-->普通函数优先级高
//2.函数模板之间重载
//  不需要付出额外代价的函数模板优先级高
//  参数约束更严格优先级更高
template<typename T>
T print(T t1, T t2)
{
    cout << "template func   1" << endl;
    cout << t1 << "   " << t2 << endl; 
    return t1+t2;
}
template<typename T,typename U>
T print(T t, U u)
{
    cout << "template func   2" << endl;
    cout << u << "   " << t << endl; 
    return u+t;
}

void test1()
{
    double x = 9.1;
    int y = 10;
    print<int>(x,y);  //模板1
    //T = int ,print(int , int)
    //模板2：
    //T = int ,print(int,int)
    //U需要编译器推导，此时y的类型是int，所以推出u是int

    //参数(double,int)
    print<int>(y,x);  //模板2
    //T= int U = double(根据第二个参数)
    //int print(int , double)   参数(int,double)

}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

