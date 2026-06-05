#include <iostream>
#include<string>
#include<fstream>

using namespace std;

//按单词读取
void test1(){
    ifstream ifs {"1.txt"};
    string word;
    while(ifs >> word)
    {
        cout << word << endl;
    }
    cout << endl;
}

//按行读取
void test2()
{
    ifstream ifs{"1.txt"};
    string line;

    while(getline(ifs,line))
    {
        cout << line << endl;
    }

}

int main(int argc,char *argv[])
{
    test1();
    test2();

    return 0;
}

