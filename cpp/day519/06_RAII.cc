#include <iostream>

using namespace std;

template<typename T>
class RAII
{
public:
    //构造函数初始化
    RAII( T *p )
    :m_p(p)
    {
        cout << "init resource" << endl;
    }
    //析构函数，释放资源
    ~RAII()
    {
        cout << "release resources " << endl;
        if(m_p)
        {
            delete m_p;
            m_p = nullptr;
        }
    }
    //删除拷贝类型的函数
    RAII(const RAII &) = delete;
    RAII &operator=(const RAII &) = delete;
    
    //提供访问资源的相关操作
    //operator->
    T *operator->()
    {
        return m_p;
    }
    T &operator*()
    {
        return *m_p;
    }
    T *get()
    {
        return m_p;
    }
private:
    //资源类型的指针 //底层指针，裸指针，原始指针
    T *m_p;

};

class Point
{
public:
    Point(int x ,int y)
    :m_x(x)
    ,m_y(y)
    {
        cout << "Point" << endl;
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
    RAII<int> raii{new int{100}};
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

