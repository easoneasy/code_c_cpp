#include <iostream>
#include <vector>
#include <list>
#include <deque>

using namespace std;
//练习list与deque的insert操作，理解更新迭代器的意义，
//试验vector的insert操作

void print(vector<int> &box)
{
    for(auto & e : box)
    {
        cout << e << " ";
    }
    cout << endl;
}

//定义函数模板
template<typename Container>
void print(Container &box)
{
    for(auto & e : box)
    {
        cout << e << " ";
    }
    cout << endl;
}

//insert,list,不更新迭代器
void test1()
{
    list<int> box{1,2,3,4,5};
    print(box);
    //定义迭代器
    auto it = box.begin();
    ++it;
    cout << "*it " << *it << endl;
    cout << "---------" << endl;
    box.insert(it,10);
    print(box);
    cout << "*it " << *it << endl;
    cout << "---------" << endl;
    box.insert(it,2,200);
    print(box);
    cout << "*it " << *it << endl;
}

//insert,list,更新迭代器
void test2()
{
    list<int> box{1,2,3,4,5};
    print(box);
    //定义迭代器
    auto it = box.begin();
    ++it;
    cout << "*it " << *it << endl;
    cout << "---------" << endl;
    it = box.insert(it,10);
    print(box);
    cout << "*it " << *it << endl;
    cout << "---------" << endl;
    it = box.insert(it,2,200);
    print(box);
    cout << "*it " << *it << endl;
}

//deque,insert,不更新迭代器
void test3()
{
    deque<int> box {1,2,3,4,5};
    print(box);
    auto it = box.begin();
    ++it;
    cout << "*it : " << *it << endl;
    cout << "---------" << endl;
    box.insert(it,100);
    print(box);
    cout << "*it : " << *it << endl;
    cout << "---------" << endl;
    box.insert(it,2,200);
    print(box);
    cout << "*it : " << *it << endl;
}
//deque,insert,不更新迭代器
void test4()
{
    deque<int> box {1,2,3,4,5};
    print(box);
    auto it = box.begin();
    ++it;
    cout << "*it : " << *it << endl;
    cout << "---------" << endl;
    it = box.insert(it,100);
    print(box);
    cout << "*it : " << *it << endl;
    cout << "---------" << endl;
    it = box.insert(it,2,200);
    print(box);
    cout << "*it : " << *it << endl;
}

//vector,insert,不更新迭代器,会发生段错误，需要更新
void test5()
{
    vector<int> box {1,2,3,4,5};
    print(box);
    auto it = box.begin();
    ++it;
    cout << "*it : " << *it << endl;
    cout << "---------" << endl;
    it = box.insert(it,100);
    print(box);
    cout << "*it : " << *it << endl;
    cout << "---------" << endl;
    it = box.insert(it,2,200);
    print(box);
    cout << "*it : " << *it << endl;
}

int main(int argc,char *argv[])
{

    // test1();
    // test2();
    // test3();
    // test4();
    test5();

    return 0;
}

