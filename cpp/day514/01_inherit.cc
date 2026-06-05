#include <iostream>

using namespace std;
class Point
{
public:
    Point(int a =0 , int b = 0)
    {
        x = a;
        y = b;
    }
    void move(int xoffset,int yoffset)
    {
        x += xoffset;
        y += yoffset;
    }
    int getx()
    {
        return x;
    }
    int gety()
    {
        return y;
    }
private:
    int x,y;
};
class Rectangle
:protected Point
{
public:
    Rectangle(int x,int y,int l ,int w)
    :Point(x,y)
    {
        length = l;
        width = w;
    }
    int getLength()
    {
        return length;
    }
    int getWidth()
    {
        return width;
    }
    void move(int xoffset,int yoffset)
    {
        return Point::move(xoffset,yoffset);
    }
    int getx()
    {
        return Point::getx();
    }
    int gety()
    {
        return Point::gety();
    }
private:
    int length;
    int width;

};
void test1()
{
    Rectangle r(0,0,8,4);
    r.move(23,56);
    cout << r.getx() << "," << r.gety() << ","
    << r.getLength() << "," << r.getWidth() << endl;

}
int main(int argc,char *argv[])
{
   
   test1();
   return 0;
}
