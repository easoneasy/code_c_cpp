#include <iostream>
#include <map>
#include <string.h>
#include <utility>
using namespace std;

void test1()
{
    map<int,string> m{
        {2,"aaa"},
        {5,"bbb"},
        {1,"ccc"}
    };
    cout << m[1] << endl;
    m[2] = "ddd";
    cout << m[2] << endl;
    m[4]="fff";
    for(auto &e:m)
    {
        cout << e.first << " = " << e.second << endl;
    }
}

void test2()
{
    map<string,int> m{
        {"zs",20},
        {"ls",19},
        {"zz",23}
    };
    cout << m["zs"]<< endl;
    m["ls"] = 22;
    m["ww"];
    for(auto &e : m)
    {
        cout << e.first << " = " << e.second << endl;
    }

}

int main(int argc,char *argv[])
{

    // test1();
    test2();

    return 0;
}

