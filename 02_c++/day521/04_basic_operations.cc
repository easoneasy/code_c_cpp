#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <deque>

using namespace std;

void print()
{

}

//vector初始化操作
void test1()
{
    //无参操作
    vector<int> box1;
    //初始化列表
    vector<int> box2;
    //拷贝构造
    vector<int> box3{box2};
    //vector<int> box3 = box2;
    //迭代器范围
    vector<int> box4{box2.begin(),box2.end()};
    //count 个 value
    vector<int> box5(3,100); //3个100
}

//list初始化
void test2()
{
    //无参操作
    list<int> box1;
    //初始化列表
    list<int> box2;
    //拷贝构造
    list<int> box3{box2};
    //vector<int> box3 = box2;
    //迭代器范围
    list<int> box4{box2.begin(),box2.end()};
    //count 个 value
    list<int> box5(3,100); //3个100
}

//deque初始化
void test3()
{
    //无参操作
    deque<int> box1;
    //初始化列表
    deque<int> box2;
    //拷贝构造
    deque<int> box3{box2};
    //vector<int> box3 = box2;
    //迭代器范围
    deque<int> box4{box2.begin(),box2.end()};
    //count 个 value
    deque<int> box5(3,100); //3个100
}

//容器遍历
void test4()
{
    vector<int> box1{1,2,3,4,5};
    //for i 下标遍历
    for (size_t i = 0; i < box1.size(); i++)
    {
        cout << box1[i] << " " ;
    }
    cout << endl;
    
    //迭代器遍历
    //foreach遍历
}


int main(int argc,char *argv[])
{

    test1();

    return 0;
}

