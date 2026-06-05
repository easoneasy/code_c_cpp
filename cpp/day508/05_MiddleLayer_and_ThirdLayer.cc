#include <iostream>
using namespace std;
//第一层
class Data
{
public:
    Data()
    {
        cout << "Data()" << endl;
    }
    int getData()
    {
        return m_data;
    }

private:
    int m_data = 1;
};
//第二层
class MiddleLayer
{
public:
    MiddleLayer(Data *p)
    :m_p(p)
    {
        cout << "MiddleLayer(Data *)" << endl;
    }

    ~MiddleLayer()
    {
        cout << "~MiddleLayer" << endl;
        if(m_p)
        {
            delete m_p;
            m_p = nullptr;
        }
    }
    //重载指针
    //返回Data的原生指针
    Data *operator->()
    {
        return m_p;
    }
    //重载解引用
    Data &operator*()
    {
        return *m_p;
    }
private:
    Data *m_p;
};
//第三层
class ThirdLayer
{
public:
    ThirdLayer(MiddleLayer *ml)
    :m_pml(ml)
    {
        cout << "ThirdLayer()" << endl;
    }
    ~ThirdLayer()
    {
        cout << "~ThirdLayer" << endl;
        if(m_pml)
        {
            delete m_pml;
            m_pml = nullptr;
        }
    }
    //重载箭头
    //返回Middle对象（引用）
    MiddleLayer &operator->()
    {
        cout << "operator ->" << endl;
        return *m_pml;
    }
private:
    MiddleLayer *m_pml;
};
void test1(){

    ThirdLayer p {new MiddleLayer{new Data{}}};
    p->getData();
}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

