#include <iostream>
#include<string>
#include<fstream>

using namespace std;

void test1(){
    ifstream ifs{"1.txt"};
    char ch;
    while((ch = ifs.get()) != -1)
    {
        cout << ch << endl;
    }
    ifs.close();
}
void test2()
{
    ifstream ifs{"2.txt"};
    string word;
    while(!ifs.eof())
    /* while(ifs >> word) */
    {
        ifs >> word;
        cout << word << endl;
    }
    ifs.close();
}

int main(int argc,char *argv[])
{
    /* test1(); */
    test2();
    return 0;
}

