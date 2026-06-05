#include <iostream>
#include <string>
using namespace std;

template<typename T>
class Stack
{
public:
    //构造函数
    //对数据成员初始化
    Stack(int init_capacity = 4)
    :m_capacity(init_capacity)
    ,m_top(0)
    {
        m_data = new T[m_capacity];
    }
    //析构函数
    ~Stack()
    {
        if(m_data)
        {
            delete [] m_data;
            m_data = nullptr;
        }
    }
    //判断栈是否为空
    bool empty() const 
    {
        return m_top == 0;
    }
    //获取栈中元素的个数
    int size() const
    {
        return m_top;
    }
    //入栈
    void push(const T &t)
    {
        //栈满自动扩容
        if(m_top == m_capacity)
        {
            //扩容
        }
        m_data[m_top++] = t;
    }
    //出栈
    void pop()
    {
        if(empty())
        {
            cout << "stack is empty" << endl;
        }
        --m_top;
    }
    //获取栈顶元素
    T top() const
    {
        if(empty())
        {
            cout << "stack is empty top() failed" << endl;
        }
        return m_data[m_top - 1];
    }

private:
    T *m_data;  //指向动态分配数组的指针，存放栈元素
    int m_top;  //栈顶指针（当前栈内元素的个数，下一个入栈的位置）
    int m_capacity; //栈的容量
};

void test1()
{
    Stack<int> i(2);
    cout << i.empty() << endl;
    i.push(10);
    i.push(20);
    i.pop();
    cout << i.size()<< endl;
    cout << i.top() << endl;
    cout << "---------" << endl;
    Stack<double> d(3);
    cout << d.empty() << endl;
    d.push(1.1);
    d.push(2.2);
    d.push(3.3);
    d.pop();
    cout << d.size() << endl;
    cout << d.top() << endl;
    cout << "--------" << endl;
    Stack<string> s(4);
    cout << s.empty() << endl;
    s.push("hello");
    s.push("world");
    s.push("hi");
    s.pop();
    cout << s.size() << endl;
    cout << s.top() << endl;
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

