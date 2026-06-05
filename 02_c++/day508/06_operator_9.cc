#include <iostream>
using namespace std;
class Base
{
public:
    //构造函数
    Base(int num)
        :m_num(num)
    {
        cout << "Base(int)" << endl;
    }
    friend
    Base operator+(const Base &l ,const Base &r);

    friend
    bool operator==(const Base &obj,int num);
private:
    int m_num;
};

//+重载
Base operator+(const Base &l ,const Base &r)
{
    return Base{r.m_num - l.m_num}; 
}
//==重载
bool operator==(const Base &obj,int num)
{
    if(obj.m_num == num)
    {
        return true;
    }else
    {
        return false;
    }
}
void test1(){
    int i = 2;
    int j = 7;
    Base x(i);
    Base y(j);
    cout << (x+y == j-i) << endl;
}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

