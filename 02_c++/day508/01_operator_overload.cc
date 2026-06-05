#include <iostream>
using namespace std;

class Point
{
public:
    Point()=default;
    Point(int x,int y)
    :m_x(x)
     ,m_y(y)
    {
        cout << "Point(int,int)" << endl;
    }
    void print()
    {
        cout << m_x <<" " << m_y << endl;
    }

    friend
    ostream & operator<<(ostream &os , Point &pt);

    friend
    istream & operator>>(istream & is ,Point &pt);
    
    friend
    Point operator+(const Point &lhs,const Point &rhs);
    friend
    Point operator-(const Point & lhs, const Point &rhs);
private:
    int m_x;
    int m_y;
};
//加法重载
Point operator+(const Point &lhs,const Point &rhs)
{

    return Point{lhs.m_x+rhs.m_x,lhs.m_y+rhs.m_y};
}
//减法重载
Point operator-(const Point & lhs, const Point &rhs)
{
    return Point{lhs.m_x-rhs.m_x,lhs.m_y-rhs.m_y};
}
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
    Point pt3=pt1+pt2;
    cout << pt3 << endl;
    cout << "---------" << endl;
    cout << "请输入两个数字" << endl;
    Point pt4;
    cin >> pt4;
    cout << pt4 << endl;
    Point pt5 = pt2 - pt1;
    cout << pt5;
}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

