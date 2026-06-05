#include <iostream>

using namespace std;

class Count{
public:
    //设置构造函数、输入默认值
    Count(int length , int width)
    :m_length(length)
    ,m_width(width)
    {
        cout << "constructor" << endl;
    }
    //设置周长
    void  setCircum(){

        circum = ( m_length + m_width ) *2;
        cout << "circum: " << circum << endl;
    }
    void setArea(){

        area = m_length * m_width;
        cout << "area: " << area << endl;
    }
    void getCout(){
        cout << m_length << " " << m_width << endl;
    }
private:
    int m_length;
    int m_width;
    int circum;
    int area;
};


void test1()
{
    Count c1(3,4);
    c1.setCircum();
    c1.setArea();
    c1.getCout();

}
int main(int argc,char *argv[])
{
   
   test1();
   return 0;
}
