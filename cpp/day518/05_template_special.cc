#include <iostream>
#include <string.h>
using namespace std;

//模板的特化：
//针对某种特殊类型，普通函数模板处理不了专门针对该类型进行特殊处理
//template<typename T>
//void func(特殊类型)(参数列表)<>

//普通通用模板
template<typename T>
T add (T t1,T t2)
{
    cout << "add(T,T)" << endl;
    return t1+t2;
}
class Complex;
//模板的特化
//需要依赖通用模板，通用模板不匹配才会使用特化模板
template<>
const char *add<const char*>(const char* c1,const char *c2)
{
    char *temp = new char[strlen(c1)+strlen(c2)+1]{};
    strcpy(temp,c1);
    strcat(temp,c2);
    return temp;
}

void test1()
{
    cout << add<int>(1,2) << endl;
    cout << add("ab","cd") << endl;
    // add<Complex>(cx1,cx2);
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

