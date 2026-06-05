#include <iostream>

using namespace std;

//类模板：把模板作用于类上
//template<typename T>
//class Box
//{
//  
//}
//在类中可以正常使用T类型
//

class Data
{
public:
    int getData()
    {
        return m_data;
    }
private:
    int m_data;

};
//希望管理者可以管理不同类型的数据
//使用模板
class MiddleLayer
{
public:
    MiddleLayer(Data *p)
    :m_p(p)
    {

    }
    ~MiddleLayer()
    {
        delete m_p;
    }
    Data *operator->()
    {
        return m_p;
    }
    Data &operator*()
    {
        return *m_p;
    }
private:
    //  T *m_p;
    Data *m_p;
};

void test1()
{
    MiddleLayer ml{new Data{}};
    ml->getData();
    (*ml).getData();
}

template<typename T = int>
class Box
{
public:
    Box(T data)
    :m_data(data)
    {

    }
    //成员函数
    void print(T t)
    {
        cout << m_data << endl;
    }
    //声明和实现分开
    void print2(T t);
private:
    T m_data;
};

//类外实现成员函数
//要再写一遍模板
//不要写默认值
template<typename T>
//Box<需要加上模板的类型>
void Box<T>::print2(T t)
{
    cout << "print2()" << endl;
}
void test2()
{
    //显式实例化
    Box<int> box1{100};
    Box<double> box2{3.14};
    Box<string> box3{"abc"};
    //隐式实例化
    // Box box4{100};    // ？？
    // Box<> box4{100};  //  ？？
}

int main(int argc,char *argv[])
{

    // test1();
    test2();

    return 0;
}