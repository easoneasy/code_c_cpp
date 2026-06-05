#include <iostream>
using namespace std;

void test1(){

    int num1 = 1;
    int num2 = 2;
    int const *p = &num1;
    /* *p = 3; */
    cout << *p <<endl;
    p = &num2;
    cout << *p <<endl;
    
}

int main(int argc,char *argv[])
{
    test1();



    return 0;
}

