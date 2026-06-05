#include <iostream>

using namespace std;

//把模板作用在函数上

// int add(int a ,int b)
// {
//     return a+b;
// }

//定义模板的关键字 template
//T:类型参数/模板参数,可以是任意的字母
// template<typename T> //T是类型，不知道是什么类型-->通用
//用的时候才知道是什么类型，将类型参数化
template<typename T>
T add(T a ,T b)
{
    cout << "使用了模板" << endl;
    return a+b;
}

void test1()
{
    add(1,2);
    add(1.1,2.2);
    string s1 ="hello";
    string s2 = "world";
    add(s1,s2);
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

