#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
/*
std::move()
主要做类型转换：把一个左值转换成一个右值
只是类型转换，不涉及资源的转移（取决于移动相关的函数）
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

//move只是进行类型转换，不涉及资源转移
void test1()
{
   String s{"hello"};    //左值
//    &move(s);          //左值-->右值

    String s2 {"world"};
    s2 = s;              //调用普通赋值构造
    // s2 = move(s);     //调用移动赋值构造函数
}

//拷贝构造
void test2()
{
    vector<int> v1{1,2,3};
    vector<int> v2 = v1;      //调用拷贝构造
    cout << "v1 size " <<v1.size()<< endl;
    cout << "v2 size " <<v2.size()<< endl;
}

void test3()
{
    vector<int> v1{1,2,3};
    vector<int> v2 = move(v1);
    cout << "v1 size " <<v1.size()<< endl;
    cout << "v2 size " <<v2.size()<< endl;
}

int main(int argc,char *argv[])
{
    // test1();
    // test2();
    test3();
    return 0;
}

