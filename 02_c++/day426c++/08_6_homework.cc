#include <iostream>
using namespace std;

void test1(){
static int hot = 200;

int & rad = hot;

hot = hot + 100;

cout << rad << endl;
}

int main(int argc,char *argv[])
{
    test1();



    return 0;
}

