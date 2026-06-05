#include <iostream>

using namespace std;

class Figure {
public:
    virtual string getName() const = 0;
    virtual double getArea() const = 0;
};

class Rectangle
:public Figure
{
public:
    Rectangle(int x, int y)
    :r_x(x)
    ,r_y(y)
    {
        cout << "Rectangle constructor" << endl;
    }
    virtual double getArea() const override
    {
        return (r_x * r_y);
    }
    virtual string getName() const override
    {
        
        return "Rectangle" ;
    }
    int r_x;
    int r_y;
};

class Circle
:public Figure
{
public:
    Circle(int x)
    :c_x(x)
    {
        cout << "Circle constructor" << endl;
    }
    virtual double getArea() const override
    {
        return 3.14*c_x*c_x;
    }
        virtual string getName() const override
    {
        
        return "Circle" ;
    }
    int c_x;
};

class Triangle
:public Figure
{
public:
    Triangle(int x, int y ,int z)
    :t_x(x)
    ,t_y(y)
    ,t_z(z)
    {
        cout << "Triangle constructor" << endl;
    }
    virtual double getArea() const override
    {
        return (t_x * t_y) / 2.0;
    }
    virtual string getName() const override
    {
        
        return "Triangle" ;
    }
    int t_x;
    int t_y;
    int t_z;

};

void display(Figure & fig) {
    cout << fig.getName() 
         << "的面积是:" 
         << fig.getArea() << endl ;
}

void test() {
    Rectangle r(10, 20);
    Circle c(15);
    Triangle t(3, 4, 5);
    display(r);
    display(c);
    display(t);
}

int main(int argc,char *argv[])
{

    test();

    return 0;
}

