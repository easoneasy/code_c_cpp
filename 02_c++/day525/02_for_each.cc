#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Func
{
    void operator()(int num)
    {
        cout << num << " ";
    }
};

void test1()
{
    vector<int> box{1,2,3,4,5};
    for_each(box.begin(),box.end(),Func());
    cout << endl;
}

//使用lambda表达式
void test2()
{
    vector<int> box{1,2,3,4,5};
    for_each(box.begin(),box.end(),
        [](int num)->void{cout << num << " ";   //lambda表达式
    });
    cout << endl;
}

int main(int argc,char *argv[])
{

    // test1();
    test2();
    return 0;
}

