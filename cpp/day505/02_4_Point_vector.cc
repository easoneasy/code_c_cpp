#include <iostream>
#include<vector>
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
    Point(int x,int y)
    :m_x(x)
    ,m_y(y)
    {
        cout << "Point(int,int)" << endl;
    }
    //拷贝构造函数
    Point (const Point & rhs)
    :m_x(rhs.m_x)
    ,m_y(rhs.m_y)
    {
        cout << "Point(const Point & rhs)" << endl; 
    }
    //赋值运算符函数
    Point &operator=(const Point &rhs)
    {
        cout << "operator=" << endl;
        return *this;
    }
    //析构函数
    ~Point()
    {
        cout << "~Point" << endl;
    }
    //打印
    void print()
    {
        cout << m_x << " " << m_y << endl;
    }

private:
    int m_x;
    int m_y;
};
void test1(){

    vector<Point> box;
    box.reserve(5);
    Point pt1{1,1};
    Point pt2{2,2};
    box.push_back(pt1);
    box.push_back(pt2);
    box[0].print();
    auto it = box.begin();
    it->print();
    ++it;
    it->print();
}

int main(int argc,char *argv[])
{
    test1();



    return 0;
}

