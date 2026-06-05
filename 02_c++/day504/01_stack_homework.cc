#include<stdlib.h>
#include <iostream>
using namespace std;
//只能生成栈对象
class Point
{
public:
    //构造函数
    Point(int x, int y)
    :m_x(x)
    ,m_y(y)
    {
        cout << "Point()" << endl;
    }
    //析构函数
    ~Point()
    {
        cout << "~Point()" << endl;
    }
    void print()
    {
        cout << m_x << " " << m_y << endl;
    }
private:
    void *operator new(size_t size)
    {
        cout << "operator new " << endl;
        return malloc(size);
    }
    
    void operator delete(void *p)
    {
        cout << "operator delete" << endl;
        free(p);
    }

private:
    int m_x;
    int m_y;
};
void test1(){
    Point pt1 = {1,1};
    /* Point *pt2 = new Point{1,1}; */
    /* delete pt2; */
}

int main(int argc,char *argv[])
{
    test1();



    return 0;
}

