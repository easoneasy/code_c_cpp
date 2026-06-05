#include <iostream>
using namespace std;

int divide(int x , int y){
    if(y==0){
        throw "y is illegal";
    }
    return x/y;
}

int main(int argc,char *argv[])
{
        try{
            divide(10,0);
        }catch(const char * msg){
            cout << msg << endl;
        }

    return 0;
}

