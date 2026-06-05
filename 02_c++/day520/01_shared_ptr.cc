#include <iostream>
#include <memory>
#include <vector>
using namespace std;
/*
    shared_ptr：共享所有权的智能指针
    可以复制、赋值操作   --->  进行共享所有权
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

//创建shared_ptr对象
void test1()
{
    shared_ptr<Point> sp{new Point{1,1}};
    shared_ptr<Point> sp2 = make_shared<Point> (3,4);
}

void test2()
{
    shared_ptr<Point> sp{new Point{1,1}};
    sp->print();
    (*sp).print();
    sp.get()->print();
}

//测试共享所有权
//合法的共享
void test3()
{
    shared_ptr<Point> sp{new Point{1,1}};
    cout << "sp:count" << sp.use_count() << endl;
    shared_ptr<Point> sp2 = sp;  //调用拷贝构造函数
    sp->print();
    sp2->print();  
    cout << "-----------" << endl;
    cout << "sp:count" << sp.use_count() << endl;
    cout << "sp2:count" << sp2.use_count() << endl;
    cout << "-----------" << endl;
    shared_ptr<Point> sp3{new Point{3,3}};
    sp3 = sp;
    cout << "sp:count" << sp.use_count() << endl;
    cout << "sp2:count" << sp2.use_count() << endl;
    cout << "sp3:count" << sp3.use_count() << endl;

}

//非法的共享
void test4()
{
    //原始指针暴露
    Point *p =new Point{1,1};
    //
    shared_ptr<Point> sp1 {p};
    sp1->print();
    cout << "-----------" << endl;
    //把原始指针交给另一个智能指针管理
    shared_ptr<Point> sp2 {p};
    sp2->print();
    cout << "-----------" << endl;
    //智能指针的计数器都为1，并没有实现 共享
    cout << "sp count " << sp1.use_count() << endl;
    cout << "sp2 count " << sp2.use_count() << endl;
    //会出现double free
}
//其他形式的非法共享
void test5()
{
    shared_ptr<Point> sp1{new Point{1,1}};
    //将sp1的原始指针交给sp2
    shared_ptr<Point> sp2{sp1.get()};  
    sp1->print();
    sp2->print();
    cout << "sp count " << sp1.use_count() << endl;
    cout << "sp2 count " << sp2.use_count() << endl;

}

void test6()
{
    vector<shared_ptr<Point>> v;
    shared_ptr<Point> sp1{new Point{1,1}};
    shared_ptr<Point> sp2{new Point{2,2}};
    shared_ptr<Point> sp3{new Point{3,3}};
    v.push_back(sp1);
    v.push_back(sp2);
    v.push_back(sp2);
    v[0]->print();
}

int main(int argc,char *argv[])
{

    // test1();
    // test1();
    // test3();
    // test4();
    // test5();
    test6();

    return 0;
}

