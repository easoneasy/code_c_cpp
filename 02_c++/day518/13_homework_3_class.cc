#include <iostream>

using namespace std;

//类模板
template <typename T = int>
class Box
{
public:
    Box(T data)
    :m_data(data)
    {
        cout << "Box(T data) constructor" << endl;
    }
    //成员函数
    void print(T t)
    {
        cout << "print()" << endl;
    }
    //声明与实现分开写
    void print2(T t);

private:
T m_data;
};

template<typename T>
void Box<T>::print2(T t)
{
    cout << "print2()" << endl;
}

void test1()
{
    //显式实例化
    Box<int> box1{100};
    Box<double> box2{3.14};
    Box<string> box3{"abc"};
    //隐式实例化
    Box box4{100};
    Box<> box5{200};
    box4.print2(10);
}

//函数模板
template <typename T ,typename U>
T print(T t,U u)
{
    cout << "template  1 " << endl;
    return t;
}

template <typename T ,typename U>
T print(U u,T t)
{
    cout << "template  2 " << endl;
    return t;
}

void test2()
{
    int x = 1;
    double y = 3.14;
    print<int,double>(x,y);
    print<double,int>(x,y);
}

int main(int argc,char *argv[])
{

    // test1();
    test2();

    return 0;
}

