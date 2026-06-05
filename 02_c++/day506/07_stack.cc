#include <iostream>
using namespace std;

class Stack
{
public:
    //构造函数
    Stack(int size =10)
    :m_ssize(size)
     ,m_stop(-1)
     ,m_sdata(new int[m_ssize]{})
    {
        cout << "Stack(int size)" << endl;
    }
    //析构函数
    ~Stack()
    {
        cout << "~Stack()" << endl;
        if(m_sdata)
        {
            delete [] m_sdata;
            m_sdata = nullptr;
        }
    }
    bool full() const
    {
        return m_stop == m_ssize -1;
    }
    bool empty() const
    {
        return -1 == m_stop;
    }
    void push(const int &value)
    {
        if(!full())
        {
            m_sdata[++m_stop] = value;
        }else{
            cout << "The Stack is Full" << endl;
            return;
        }
    }
    void pop()
    {
        if(!empty())
        {
            --m_stop;
        }else
        {
            cout << "The Stack is Empty" << endl;
            return;
        }
    }
    int top() const
    {
        if(!empty())
        {
            return m_sdata[m_stop];
        }else{
            throw "Stack is Empty";
        }
    }

private:
    int m_ssize;
    int m_stop;
    int *m_sdata;
};
void test1(){
    Stack st(12);
    cout <<"栈是不是空的" << st.empty() << endl;
    st.push(1);
    cout << "栈是不是满的" << st.full() << endl;
}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

