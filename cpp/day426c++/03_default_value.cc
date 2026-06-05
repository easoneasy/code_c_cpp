#include <iostream>
using namespace std;

void func(int a = 1,int b = 0){
    cout << "a=" << a <<endl;
    cout << "b=" << b <<endl;
}

void test1(){
    func();

}

int main(int argc,char *argv[])
{
    test1();



    return 0;
}

