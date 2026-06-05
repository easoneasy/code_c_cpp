#include <iostream>
#include <memory>
#include <vector>
using namespace std;

/*
unique_ptr智能指针：独占资源的所有权
不允许复制相关的操作：拷贝构造、赋值运算符函数删除
unique_ptr作为容器中的元素
*/
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

//基本使用
void test1()
{
    //把资源交给智能指针管理
    //利用构造函数创建的智能指针对象
    unique_ptr<Point> up{new Point{1,2}};
    //还可以用make_unique函数创建智能指针
    up->print();        //获取指针
    (*up).print();
    up.get()->print();
}

//测试独占所有权
void test2()
{
    unique_ptr<Point> up{new Point{1,2}};
    //测试拷贝构造
    // unique_ptr<Point>up2 = up;  //error 拷贝构造被删除，不允许复制
    unique_ptr<Point> up3 {new Point{3,4}};
    // up3 = up;  //error 赋值运算符函数被删除

}

//作为容器元素
void test3()
{
    //定义了智能指针的容器
    vector<unique_ptr<Point>> v; 
    unique_ptr<Point> up1{new Point{1,1}};
    unique_ptr<Point> up2{new Point{2,2}};
    unique_ptr<Point> up3{new Point{3,3}};
    unique_ptr<Point> up4{new Point{4,4}};
    up1->print(); //可以访问元素
    //把元素放入到vector中,直接放左值对象会报错
    //push_back传参时会调用拷贝，但是这里没有拷贝函数
    //改进：将左值-->右值，使用移动函数
    // v.push_back(up1);
    // v.push_back(up2);
    // v.push_back(up3);
    // v.push_back(up4);
    v.push_back(move(up1));
    v.push_back(move(up2));
    v.push_back(move(up3));
    v.push_back(move(up4));
    v[0]->print();
    cout << "----------" << endl;
    //up1,up2...的资源被转移,不再管理资源
    up1->print();

}

void test4()
{
    unique_ptr<Point> up1{new Point{1,1}};
    up1->print();
    //reset()替换被管理的对象,原来的对象销毁自动调用析构函数
    up1.reset(new Point{3,4});
    up1->print();
}
void test5()
{
    // unique_ptr<Point> up {new Point{1,1}};
    unique_ptr<Point> up1 = make_unique<Point>(1,1);
    up1->print();
}

int main(int argc,char *argv[])
{

    // test1();
    // test3();
    // test4();
    test5();

    return 0;
}

