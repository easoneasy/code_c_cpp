#include <iostream>
using namespace std;

class Point
{
public:
    //无参构造函数
    Point()
    {
        cout << "Point()" << endl;
    }
    //有参构造函数
    Point(int x , int y)
    {
        m_x = x;
        m_y = y;
        cout << "point(int,int)" << endl;
    }
private:
    int m_x;
    int m_y;
};


void test1(){
    Point p1;
    Point p2(1,2);
    //调用无参构造函数
    Point p3{};

}

int main(int argc,char *argv[])
{
    test1();



    return 0;
}

