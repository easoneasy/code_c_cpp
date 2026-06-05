#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>
using namespace std;

/*
    bind1st
    bind2nd
    绑定函数参数，绑定二元函数的参数为某个固定值
*/

void test1()
{
    vector<int> box{1,2,3,4,5};
    //使用remove_if删除大于3的元素
    //remove_if的第三个参数是函数对象，直接写less报错
    //bind1st绑定lhs为3
    auto it = remove_if(box.begin(),box.end(),bind1st(less<int>(),3));
    box.erase(it,box.end());
    for_each(box.begin(),box.end(),
        [](int num){
            cout << num <<" ";
        }
    );
    cout << endl;
}

//使用bind2nd绑定rhs为3
void test2()
{
    vector<int> box{1,2,3,4,5};
    auto it = remove_if(box.begin(),box.end(),bind2nd(less<int>(),3));
    box.erase(it,box.end());
    for_each(box.begin(),box.end(),
        [](int num){
            cout << num << " ";
        }
    );
    cout << endl;
}

int main(int argc,char *argv[])
{

    // test1();
    test2();

    return 0;
}

