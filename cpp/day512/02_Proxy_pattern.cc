#include <iostream>
using namespace std;

#if 0
//委托类
class JingTian
{
public:
    void buyBreakFast()
    {
        cout << "买两个包子" << endl;
    }
};
//代理类
class KongLing
{
public:
    KongLing(JingTian &jt)
    :m_jt(jt)
    {
        cout << "KongLing" << endl;
    }
    void buyBreakFast()
    {        
        cout << "帮景天" << endl;
        m_jt.buyBreakFast();
    }
    //将委托设置为数据成员
    JingTian & m_jt;
};

void test1(){
    JingTian jt;
    KongLing kl{jt};
    kl.buyBreakFast();
}

#endif

class JingTian
{
public:
    void buyBreakFast()
    {
        cout << "买两个包子" << endl;
    }
};
//代理类，设置为父类
class KongLing : public JingTian
{
public:
    void buyBreakFast()
    {
        cout << "帮景天" << endl;
        //调用父类的同名成员函数
        //通过类名作用域调用
        JingTian::buyBreakFast();
    }

};
void test2()
{
    KongLing kl;
    kl.buyBreakFast();
}
int main(int argc,char *argv[])
{
    test2();

    return 0;
}

