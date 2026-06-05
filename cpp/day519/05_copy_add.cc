#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
/*
拷贝构造函数调用时机：
    1、一个已经存在的对象初始化新对象
    2、对象作为函数参数
    3、对象作为函数返回值

如果返回的对象生命周期即将结束(局部对象)，调用移动构造
如果返回的生命周期大于函数的周期(全局对象)，调用拷贝构造
*/

class String
{
public:
    // default no arg constructor
    String()
    /* : _pstr(nullptr) */
    : m_pstr(new char[1]())
    {
        cout << "String()" << endl;
    }
	// args constructor
    String(const char *pstr)
    : m_pstr(new char[strlen(pstr) + 1]())
    {
        cout << "String(const char *)" << endl;
        strcpy(m_pstr, pstr);
    }
	// copy constructor
    String(const String & rhs)
    : m_pstr(new char[strlen(rhs.m_pstr) + 1]())
    {
        cout << "String(const String &)" << endl;
        strcpy(m_pstr, rhs.m_pstr);
    }
	// operator =
    String & operator=(const String & rhs)
    {
        cout << "String &operator=(const String &)" << endl;
        if(this != &rhs)
        {
            if(m_pstr)
            {
                delete [] m_pstr;
            }
            m_pstr = new char[strlen(rhs.m_pstr) + 1]();
            strcpy(m_pstr, rhs.m_pstr);
        }
        return *this;
    }
	// length
    size_t length() const
    {
        size_t len = 0;
        if(m_pstr)
        {
            len = strlen(m_pstr);
        }

        return len;

    }
	// c style string
    const char * c_str() const
    {
        if(m_pstr)
        {
            return m_pstr;
        }
        else
        {
            return nullptr;
        }
    }

	// destructor
    ~String()
    {
        cout << "~String()" << endl;
        if(m_pstr)
        {
            delete [] m_pstr;
            m_pstr = nullptr;
        }
    }

    void print() const
    {
        if(m_pstr)
        {
            cout << "m_pstr = " << m_pstr << endl;
        }else{
            cout << endl;
        }
    }

    //移动构造函数
    //处理右值对象/临时对象
    //右值引用绑定临时对象
    //进行资源转移
    String(String &&rhs)
    :m_pstr(rhs.m_pstr)  //浅拷贝
    {
        cout << "move constructor" << endl;
        //把临时对象的指针设置为空
        rhs.m_pstr = nullptr;
    }
    
    //移动赋值运算符函数
    //右值引用绑定临时对象
    String& operator=(String &&rhs)
    {
        cout << "move operator = " << endl;
        //自赋值判断
        if(this != &rhs)
        {
            //回收原本空间
            delete [] m_pstr;
            //深拷贝-->浅拷贝
            //两个指针共享一个空间
            m_pstr = rhs.m_pstr;
            //将临时对象底层的指针设置为空
            rhs.m_pstr = nullptr;
        }
        //返回当前对象 *this
        return *this;
    }

private:
    char * m_pstr;
};

void func(String str)
{
    str.print();
}

void func2(String str)
{
    str.print();
}

void test1()
{
    String s{"abc"};
    // func(s);
    func2(move(s));    //调用的是移动构造
}

String func3()
{
    String s{"hello"};
    return s;          //调用移动构造函数
}
//测试对象作为参数
void test2()
{
    func3();
}

//使用的是拷贝构造函数
String str{"abc"};
String func4()
{
    return str;
}

void test3()
{
    func4();
}

int main(int argc,char *argv[])
{
    // test1();
    // test2();
    test3();

    return 0;
}