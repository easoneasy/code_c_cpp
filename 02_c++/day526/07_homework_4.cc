#include <iostream>
#include <functional>
using namespace std;

class Calculator
{
public:
    int add(int x,int y)
    {
        cout << "x : " << x << "  y : " << y << endl;
        return x+y;
    }

};

void test1()
{
    Calculator c;
    function<int(int)> f1 = bind(&Calculator::add,&c,10,placeholders::_1);
    f1(20);
    cout << "f1(20) : "<< f1(20) << endl;

    cout << "-------------" << endl;
    function<int(int)> f2 = bind(&Calculator::add,&c,placeholders::_1,20);
    f2(10);
    cout << "f2(10) : "<< f2(10) << endl;
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

