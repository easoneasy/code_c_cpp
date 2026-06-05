#include <iostream>
#include <functional>
using namespace std;

/*
    function + bind 实现函数式多态
*/

class Figure
{
public:
    virtual double area() = 0;
};

class Rectangle :public Figure
{
public:
    Rectangle(double l, double w)
    {

    }
    double m_l;
    double m_w;
};


void test1()
{

}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

