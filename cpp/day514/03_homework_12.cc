#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;

class Color
{
public:
    //构造函数
    Color(const char *color)
    :m_color(new char[strlen(color)+1]{})
    {
        strcpy(m_color,color);
    }
    //拷贝构造函数
    Color(const Color &rhs)
    :m_color(new char[strlen(rhs.m_color)+1]{})
    {
        strcpy(m_color,rhs.m_color);
    }
    //赋值运算符函数
    Color &operator=(const Color &rhs)
    {
        //自赋值判断
        if(this != &rhs)
        {
            delete [] m_color;
            m_color = new char[strlen(rhs.m_color)+1]{};
            strcpy(m_color,rhs.m_color);
        }
        return *this;
    }
    //析构函数
    ~Color()
    {
        if(m_color)
        {
            delete [] m_color;
            m_color = nullptr;
        }
    }
    //返回颜色
    char * getColor()
    {
        return m_color;
    }
    char *m_color;
};
class Point
{
public:
    //构造函数
    Point(int x ,int y)
    :m_x(x)
    ,m_y(y)
    {}
    float m_x;
    float m_y;
};
class Line
{
public:
    //构造函数
    Line(float x1,float y1,float x2,float y2)
    :pt1(x1,y1)
    ,pt2(x2,y2)
    {}
    //getLine函数
    float getLine()
    {
        float dx = pt2.m_x - pt1.m_x;
        float dy = pt2.m_y - pt1.m_y;
        return sqrt(pow(dx,2) + pow(dy,2));
    }
    Point pt1;
    Point pt2;
};
class Triangle
:public Line,public Color
{
public:
    Triangle(float x1,float y1,float x2,float y2,const char* color,float h)
    :Line(x1,y1,x2,y2)
    ,Color(color)
    ,height(h)
    {}
    //计算面积
    float getArea()
    {
        float base = getLine();
        return 0.5*base*height;
    }
    //计算周长
    float getPerimeter()
    {
        float base = getLine();
        float hypotenuse = sqrt(pow(base,2)+pow(height,2));
        return base+height+hypotenuse;
    }
    void print()
    {
        cout << "color : " << getColor() << endl;
        cout << "area : " << getArea() << endl;
        cout << "perimeter : " << getPerimeter() << endl;
    }
    float height;
};
void test1()
{
    Triangle tr{0,0,3,0,"red",4};
    tr.getColor();
    tr.getArea();
    tr.getPerimeter();
    tr.print();
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

