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
    
    //前++重载
    Point &operator++()
    {   
        this->m_x+=1;
        this->m_y+=1;
        return *this; 
    }
    
    //后++重载
    Point operator++(int)
    {
        Point tmp=*this;
        this->m_x+=1;
        this->m_y+=1;
        return tmp;
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
    cout << ++pt1;
    Point pt3 = pt1++;
    cout << pt3;
}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

