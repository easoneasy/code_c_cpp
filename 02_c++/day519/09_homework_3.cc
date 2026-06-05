#include <iostream>
#include <string.h>
using namespace std;
// 为采用深拷贝方式实现的String类
//添加移动构造函数和移动赋值运算符函数，并进行测试。
// String(String &&rhs);
// String & operator=(String &&rhs);

class String
{
public:
    //无参构造
    String()
    :m_pstr(new char[1]{})
    {
        cout << "String()" << endl;
    }
    //有参构造
    String(const char *p)
    :m_pstr(new char[strlen(p)+1]{})
    {
        cout << "String(p)" << endl;
        strcpy(m_pstr,p);
    }
    //析构函数
    ~String()
    {
        if(m_pstr)
        {
            delete [] m_pstr;
            m_pstr = nullptr;
        }
        cout << "~String" << endl;
    }
    //拷贝构造
    String(const String &rhs)
    :m_pstr(new char[strlen(rhs.m_pstr)+1]{})
    {
        strcpy(m_pstr,rhs.m_pstr);
        cout << "String(const String &)" << endl;
    }
    //赋值运算符函数
    String &operator=(const String &rhs)
    {
        cout << "operator= " << endl;
        //自赋值判断
        if(this != &rhs)
        {
            delete [] m_pstr;
            m_pstr = new char[strlen(rhs.m_pstr)+1]{};
            strcpy(m_pstr,rhs.m_pstr);
        }
        return *this;
    }
    //字符串长度
    size_t length() const
    {
        size_t len = 0;
        if(m_pstr)
        {
            len = strlen(m_pstr);
        }
        return len;
    }
    //返回c风格的字符串
    const char* c_str() const
    {
        if(m_pstr)
        {
            return m_pstr;
        }else{
            return nullptr;
        }
    }
    void print() const
    {
        if(m_pstr)
        {
            cout << "m_pstr = "<< m_pstr << endl;
        }else{
            cout << endl;
        }
    }
    //移动构造函数
    String(String &&rhs)
    :m_pstr(rhs.m_pstr)   //浅拷贝
    {
        cout << "move constructor" << endl;
        //临时对象的指针设置为空
        rhs.m_pstr = nullptr;
    } 
    //移动赋值运算符函数
    String &operator=(String &&rhs)
    {
        cout << "move operator= " << endl;
        if(this != &rhs)
        {
            delete [] m_pstr;
            m_pstr = rhs.m_pstr;
            rhs.m_pstr = nullptr;
        }
        return *this;
    }
private:
    char *m_pstr;
};


void test1()
{
    String s1{"hello"};
    String s2 = String{"hello"}; //临时对象
    s2.print();
    cout << "----------" << endl;
    String s3 = {"world"};
    s3 = move(s2);
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}