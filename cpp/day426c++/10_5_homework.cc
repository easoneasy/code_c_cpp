#include <string.h>
#include <iostream>
#include <string>
using namespace std;

void test1(){
//C字符串
    const char *pstr1 = "hello";
    char str1[20]={'w','o','r','l','d'};
    char *pstr2 = new char[20]{};
    strcat(str1,pstr1);
    strcpy(pstr2,pstr1);
    cout << pstr1 << endl;
    cout << pstr2 << endl;
    cout << str1 << endl;
    delete [] pstr2;
    pstr2 = nullptr;
//C++字符串
    string s1 = "string";
    string s2 = "strcat";
    string s3 = s1 + s2;
    cout << s3 <<endl;
    cout << s3.size() <<endl;
    cout << s3[0] <<endl;
    
}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

