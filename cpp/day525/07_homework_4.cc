#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <iterator>
using namespace std;

void test1()
{
    vector<int> src = {1,2,3,4,5};
    list<int> dst;
    auto it = src.rbegin();
    copy(src.rbegin(),src.rend(),back_inserter(dst));
    for(auto &e : dst)
    {
        cout << e << " ";
    }
    cout << endl;
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

