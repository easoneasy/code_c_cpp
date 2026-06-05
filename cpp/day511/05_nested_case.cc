#include <iostream>
using namespace std;

class Line
{
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
    private:
        int m_x;
        int m_y;
    };
public:
    Line()= default;
    Line(int x1,int y1, int x2,int y2)
    :m_pt1(x1,y1)
    ,m_pt2(x2,y2)
    {
        cout << "Line(int x4)" << endl;
    }
    void print()
    {
        m_pt1.print();
        m_pt2.print();
    }
private:
    Point m_pt1;
    Point m_pt2;

};
void test1(){
    Line line{1,2,3,4};
    line.print();
}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

