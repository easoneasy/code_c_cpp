#include <iostream>
#include <memory>
using namespace std;

/*
    weak_ptr
    没有get函数，不能直接访问资源
    在访问所引用的对象前先转换成shared_ptr  --> 使用lock函数
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

//weak_ptr基本使用
void test1()
{
    shared_ptr<Point> sp{new Point{1,1}};
    //weak_ptr的创建，接收shared_ptr
    //一般配合shared_ptr使用
    weak_ptr<Point> wp = sp;
    cout << sp.use_count() << endl;
    cout << wp.use_count() << endl;

    cout << "-------------" << endl;
    // wp->print();   //不能直接访问资源 
    //只能把weak_ptr 转化成 shared_ptr 才能访问资源
    weak_ptr<Point> wp2;
    // if(wp.lock())  //转换成功
    // if(wp2.lock())     //转换失败
    if(auto sp2 = wp.lock())   
    {
        cout << "转换成功" << endl;
    }else{
        cout << "转换失败" << endl;
    }
    cout << "--------------" << endl;
    //管理对象被删除返回true
    sp.reset(new Point{2,2});   //资源被替换了，原来的就要被删除
    cout << wp.expired() << endl;
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

