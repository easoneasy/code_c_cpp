#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
using namespace std;

void test1()
{
    ifstream ifs{"file.txt"};
    string line;
    while(getline(ifs,line))
    {
        cout << line << endl;
    }
    cout << "----------" << endl;
    cout << ifs.tellg() << endl;
    ifs.clear();
    ifs.seekg(0);
    cout << ifs.tellg() << endl;
    ofstream ofs{"data.txt"};
    string word;
    while(ifs >> word)
    {
        ofs << word << endl;
    }
    ifs.close();
}

void dealWord(string &data)
{
    auto it = data.begin();
    while(it != data.end())
    {
        if(isalpha(*it))
        {
            it++;
        }else{
            it = data.erase(it);
        }
    }
}

void test2()
{
    string a = "hell12o";
    dealWord(a);
    cout << a << endl;
}

int main(int argc,char *argv[])
{

    // test1();
    test2();

    return 0;
}

