#include <iostream>
using namespace std;

void test1(){

    int *p = new int[10]{1,2,3,4,5,6,7,8,9,10};
    for(int i = 0;i<10 ;i++){
        cout << p[i] << endl;
    }
    delete [] p;
    p = nullptr;
}

int main(int argc,char *argv[])
{
    test1();



    return 0;
}

