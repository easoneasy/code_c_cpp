#include <string.h>
#include <iostream>
using namespace std;

class Computer{
public:
    Computer(const char *brand,int price)
    :m_brand(new char[strlen(brand)+1]{})
    ,m_price(price)
    {
        
        strcpy(m_brand,brand);
        cout << m_brand << "   constructor" << endl;
    }

    void print(){
        cout << m_brand << "  " <<m_price << endl;
    }

    ~Computer(){
        cout << m_brand << "   ~Computer" << endl;
        if(m_brand){
            delete [] m_brand;
            m_brand=nullptr;
        }
    }
private:
    char *m_brand;
    int m_price;
};

Computer pc1{"pc1",100};
    // pc1.print();  不能在函数体外调用函数，可以在main中调用 

void test1(){
    pc1.print();

    Computer pc2{"pc2",200};
    pc2.print();

    static Computer pc3{"pc3",300};
    pc3.print();

    Computer *pc4 = new Computer{"pc4",400};
    pc4->print();
    delete pc4;
    pc4 = nullptr;
}

int main(int argc,char *argv[])
{
    
    test1();

    return 0;
}

