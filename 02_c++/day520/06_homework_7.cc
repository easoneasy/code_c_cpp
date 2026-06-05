#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Point
{
public:
    Point(int x ,int y)
    :m_x(x)
    ,m_y(y)
    {
        cout << "Point" << endl;
    }   
    ~Point()
    {
        cout << "~Point" << endl;
    }
    void print()
    {
        cout << m_x << " " << m_y << endl;
    }
private:
    int m_x;
    int m_y;
};

void test1()
{
    vector<unique_ptr<Point>> v;
    unique_ptr<Point> up1 {new Point{1,1}};
    unique_ptr<Point> up2 {new Point{2,2}};
    unique_ptr<Point> up3 {new Point{3,3}};
    unique_ptr<Point> up4 {new Point{4,4}};

    v.push_back(move(up1));
    v.push_back(move(up2));
    v.push_back(move(up3));
    v.push_back(move(up4));


    for(auto &e : v)
    {
        e.get()->print();
    }

}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

