#include <iostream>
#include<string.h>
using namespace std;

class Computer
{
    char *m_brand;
    double m_price;
public:
    //构造函数
    Computer(char *brand, double price)
    :m_brand(new char[strlen(brand)+1]())
    ,m_price(price)
    {
        cout << "Computer(char,double)" << endl;
        strcpy(m_brand,brand);
    }
    //析构函数
    ~Computer()
    {
        cout << "~Computer" << endl;
        if(m_brand)
        {
            delete [] m_brand;
            m_brand = nullptr;
        }
    }
    //拷贝构造函数
    Computer (const Computer & rhs)
    :m_brand(new char[strlen(rhs.m_brand)+1]())
    ,m_price(rhs.m_price)
    {
        cout << "Computer(const Computer &)" << endl;
        strcpy(m_brand,rhs.m_brand);
    }
    //赋值运算符函数
    Computer &operator=(const Computer &rhs)
    {
        cout << "&operator = " << endl;
        //自赋值判断
        if(this != &rhs)
        {
            //回收旧空间
            delete [] m_brand;
            m_brand = nullptr;
            //深拷贝
            this->m_brand = new char[strlen(rhs.m_brand)+1]{};
            strcpy(m_brand,rhs.m_brand);
        }
        //返回当前对象
        return *this;
    }
    void print()
    {
        cout << m_brand << " " << m_price << endl;
    }
};


int main(int argc,char *argv[])
{

    char str1[]="xiaomi";
    Computer pc1{str1,1999};
    pc1.print();
    Computer pc2 = pc1;
    pc2.print();
    char str2[] = "huawei";
    Computer pc3 ={str2,2999};
    pc3.print();
    pc3 = pc2;
    pc3.print();
    return 0;
}

