#include <iostream>
using namespace std;
int & func() {
    int a = 10;
    return a;
}

void test1(){
    func();
}

int main(int argc,char *argv[])
{
    test1();



    return 0;
}

