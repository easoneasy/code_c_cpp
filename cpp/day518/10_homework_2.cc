#include <iostream>

using namespace std;
//利用可变模板参数实现一个函数模板
//用来计算多个整型、浮点型数据的加法

template<typename T>
T add(T t)
{
    return t;
}

template<typename First ,typename ...Args>
First add(First first, Args ...args)
{
    return first + add(args ...);
}
void test1()
{
    cout << add(2,2,2) << endl;
}

int main(int argc,char *argv[])
{
    test1();
    return 0;
}