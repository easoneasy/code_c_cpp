#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

class Printer
{
public:
    void print(const string &s) const 
    {
        cout << s << endl;
    }
};

void test1()
{
    vector<Printer> p{3};
    for_each(p.begin(),p.end(),bind(mem_fn(&Printer::print),placeholders::_1,"Hello"));
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

