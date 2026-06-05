#include <iostream>

using std::cout;
using std::endl;
/*
 * 如果类中有const版本和非cosnt版本的成员函数
 * 1.普通对象---->非const版本的成员函数
 * 2.const对象----> const版本的成员函数
 *
 *
 * 如果类中只有非const版本的成员函数:
 * 1.普通对象---->可以调用非const版本的成员函数
 * 2.const对象--->error 因为this类型不一样
 *
 * 如果类中只有const版本的成员函数
 * 1.普通对象---->都可以调用
 * 2.const对象---->都可以调用
 *
 */
class Point
{
public:
    Point(int x, int y)
    : m_x(x)
    , m_y(y)
    {
        cout << "Point(int,int)" << endl;
    }

    // copy constructor
    Point(const Point & rhs)
    : m_x(rhs.m_x)
    , m_y(rhs.m_y)
    {
        cout << "Point(const Point &)" << endl;

    }

    void print()
    {
        cout << m_x << " " << m_y << endl;
    }
    // const 成员函数
    void show() const
    {
        cout << "show() const" << endl;
    }

    /* void show() */
    /* { */

    /*     cout << "show()" << endl; */
    /* } */ 
/* private: */
    int m_x;
    int m_y;
};

void test1()
{
    int num = 1;
    const int num2 = 2;

    Point pt{1,2};
    pt.show();
    cout << "--------" << endl;
    const Point pt2{3,4};
    pt2.show();
}


// 对象数组
// 构建对象数组形式:
// 1.通过左值对象构建数组
// 2.通过右值对象构建数组
// 3.通过初始化列表简写构建数组
void test2()
{
    // int arr[3] = {1, 2, 3}

    Point pt1{ 1, 1 };
    Point pt2{ 2, 2 };
    Point pt3{ 3, 3 };
    // 对象作为数组元素时 会调用copy
    Point pts[3] = { pt1, pt2, pt3 };
    /* pts[0].m_x = 10; */
    pts[0].print();
}

int main(int argc, char * argv[])
{
    /* test1(); */
    test2();
    return 0;
}


