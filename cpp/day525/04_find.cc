#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
using namespace std;
/*
    find ：找到了返回对应位置的迭代器，没找到返回end()
    find_if ：
*/

//返回值是查找元素的第一个元素
void test1()
{
    vector<int> box{1,2,3,4,5};
    auto it = find(box.begin(),box.end(),3);
    if(it != box.end())
    {
        cout << "find value " << endl;
        cout << *it << endl;
    }else{
        cout << "not found " << endl;
    }
}

// find_if 第三个参数是一个一元谓词，返回值为bool类型的一个参数的函数
//返回满足条件的第一个值位置的迭代器
bool func(int num)
{
    return num > 3;
}
void test2()
{
    vector<int> box{1,2,3,4,5};
    auto it = find_if(box.begin(),box.end(),func);
    if(it != box.end())
    {
        cout << "find value " << endl;
        cout << *it << endl;
    }else{
        cout << "not found " << endl;
    }
}

//replace
void test3()
{
    vector<int> box{1,2,3,4,5};
    replace(box.begin(),box.end(),3,100);
    copy(box.begin(),box.end(),ostream_iterator<int>(cout," "));
    cout << endl;
}
//replace_if
void test4()
{
    vector<int> box{1,2,3,4,5};
    replace_if(box.begin(),box.end(), 
    [](int num)->bool{    //lambda表达式，大于3的数据都替换成100
        return num > 3;
    },100
    );
    copy(box.begin(),box.end(),ostream_iterator<int>(cout," "));
    cout << endl;
}

//remove  删除元素
//1、会移动元素
//2、删除元素
void test5()
{
    vector<int> box{1,2,3,4,5};
    // remove(box.begin(),box.end(),3);
    copy(box.begin(),box.end(),ostream_iterator<int>(cout," "));
    cout << endl;
    //输出 1,2,4,5,5  //需要结合erase删除元素

    cout << "------------------" << endl;

    auto it = remove(box.begin(),box.end(),3);
    cout << *it << endl;
    box.erase(it,box.end());
    copy(box.begin(),box.end(),ostream_iterator<int>(cout," "));
    cout << endl;
}

//remove_if
void test6()
{
    vector<int> box{1,2,3,4,5};
    auto it = remove_if(box.begin(),box.end(),
        [](int num)->bool{
            return num > 3;
        }
    );
    box.erase(it,box.end());
    copy(box.begin(),box.end(),ostream_iterator<int>(cout," "));
    cout << endl;
}

int main(int argc,char *argv[])
{

    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    test6();

    return 0;
}

