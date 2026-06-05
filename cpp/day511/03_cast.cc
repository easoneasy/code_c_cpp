#include <iostream>
using namespace std;

class Complex;

class Point
{
public:
    Point(int x,int y)
    :m_x(x)
    ,m_y(y)
    {
        cout << "Point(int,int)" << endl;
    }
    void print()
    {
        cout << m_x << " " << m_y << endl;
    }
    //提供一个特殊的构造函数
    Point(const Complex &rhs);

private:
    int m_x;
    int m_y;
};
class Complex
{
public:
    Complex(int real, int image)
    : m_real(real)
    , m_image(image)
    {
        cout << "Complex(int,int)" << endl;
    }

    //类型转换函数
    /* operator Point() */
    /* { */
    /*     cout << "Complex::Complex-->Point" << endl; */
    /*     return Point{m_real,m_image}; */
    /* } */
friend
Point::Point(const Complex &rhs);
private:
    int m_real;
    int m_image;
};
//特殊参数的构造函数
Point::Point(const Complex &rhs)
:m_x(rhs.m_real)
,m_y(rhs.m_image)
{
    cout << "Point(const Complex)" << endl;
}

void test1(){
    Point pt{1,2};
    Complex cx{3,4};
    //转换数据类型
    pt = cx;
    pt.print();
}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

