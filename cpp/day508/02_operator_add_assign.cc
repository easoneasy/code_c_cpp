#include <iostream>
using namespace std;

class Point
{
public:
    //默认构造函数
    Point()=default;
    //有参构造函数
    Point(int x,int y)
    :m_x(x)
     ,m_y(y)
    {
        cout << "Point(int,int)" << endl;
    }
    //打印输出函数
    void print()
    {
        cout << m_x <<" " << m_y << endl;
    }
    //输出重载
    friend
    ostream & operator<<(ostream &os , Point &pt);
    //输入重载
    friend
    istream & operator>>(istream & is ,Point &pt);
    
    //+=重载
    Point & operator+=(const Point &rhs)
    {
        this->m_x+=rhs.m_x;
        this->m_y+=rhs.m_y;
        return *this;
    }
    //-=重载
    Point &operator-=(const Point &rhs)
    {
        this->m_x -= rhs.m_x;
        this->m_y -= rhs.m_y;
        return *this;
    }
private:
    int m_x;
    int m_y;
};
//重载输出
ostream & operator<<(ostream &os , Point &pt)
{
    os << pt.m_x << "  +  "<< pt.m_y << endl;
    return os;
}
//重载输入
istream & operator>>(istream & is ,Point &pt)
{
    is >> pt.m_x >>pt.m_y;
    return is;
}


void test1(){
    Point pt1{1,1};
    Point pt2{2,2};
    pt1 += pt2;
    pt2 -= pt1;
    cout << pt1 << endl;
    cout << pt2 << endl;
}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

