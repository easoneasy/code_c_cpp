#include <iostream>
#include <string>
#include <map>
#include <functional>

using namespace std;

int add(int a, int b)
{
    return a+b;
}

int sub(int a, int b)
{
    return a-b;
}

int multiply(int a,int b)
{
    return a*b;
}

void test1()
{
    //创建函数表
    map<string,function<int(int,int)>> calculator;
    calculator["+"] = bind(add,placeholders::_1,placeholders::_2);
    calculator["-"] = bind(sub,placeholders::_1,placeholders::_2);
    calculator["*"] = bind(multiply,placeholders::_1,placeholders::_2);

    cout << "--------计算器-----------" << endl;
    int num1,num2;
    string op;
    while(cout << "\n请输入： " && cin >> num1 >> op >> num2)
    {
        auto it = calculator.find(op);
        if(it != calculator.end())
        {
            int result = it->second(num1,num2);
            cout << "结果：" << num1 << " " << op << " " << num2 << " = " <<result << endl;
        }else{
            cout << "错误：不支持的操作符" << op << endl;
        }
    }
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

