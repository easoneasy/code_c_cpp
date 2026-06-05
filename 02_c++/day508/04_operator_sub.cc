#include <iostream>
#include<string.h>
#include<ostream>

using namespace std;

class CharArry
{
public:
    //构造函数
    CharArry(const char *pstr)
    :m_parr(new char[strlen(pstr)+1]{})
    ,m_size(strlen(pstr))
    {
        cout << "CharArry(const)" << endl;
        strcpy(m_parr,pstr);
    }
    //析构函数
    ~CharArry()
    {
        if(m_parr)
        {
            delete [] m_parr;
            m_parr = nullptr;
        }
        cout << "~CharArry" << endl;
    }
    //打印函数
    void print()
    {
        cout << m_parr << endl;
    }
    //[] 重载函数
    char &operator[](const int index)
    {
        //判断下标的合法性
        if(index >= m_size || index < 0)
        {
            cout << "index is illeagl" << endl;
            static char nullchar = '\0';
            return nullchar;
        }
        return m_parr[index];
    }
    friend
    ostream &operator<<(ostream &os,CharArry &ch);

private:
    char *m_parr;
    int m_size;
};

    //输出重载函数
    ostream &operator<<(ostream &os,CharArry &ch)
{
    os << ch.m_parr;
    return os;
}

void test1(){
    CharArry ch={"abcd"};

    cout << ch[2]<< endl;
    cout << ch << endl;
}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

