#include <iostream>
using namespace std;

int gNum=100;
const int num = 200;
void func(){
    cout << "func()" << endl;
}

void test1(){
    //局部变量
    int num1 = 10;
    //动态分配堆空间，指针是栈空间
    int *p = new int[2]{0};
    static int num2 = 20;
    const int num3 = 30;
    void (*f)()=&func;
    f();
    cout << "&gNum: " << &gNum <<endl;
    cout << "&num: " << &num <<endl;
    cout << "&num1: " << &num1 <<endl;
    cout << "&p:    " << &p <<endl;
    cout << "p:     " << p <<endl;
    cout << "&num2: " << &num2 <<endl;
    cout << "&num3: " << &num3 <<endl;
    cout << "&hello:" << &"hello" <<endl;
    cout << "f:     " << f << endl;
    printf("f   %p\n",f);
}

int main(int argc,char *argv[])
{
    test1();
    
    return 0;
}

