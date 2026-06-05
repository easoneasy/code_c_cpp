#include <iostream>
#include <vector>
#include <iterator>
#include <list>
using namespace std;

//把一个容器中的元素复制到另一个空容器中
//尾插
void test1()
{
    vector<int> box1 {1,2,3,4,5};
    vector<int> box2;

    //结合copy函数，结合迭代器适配器
    back_insert_iterator<vector<int>> it{box2};
    
    copy(box1.begin(),box1.end(),it);

    //打印数据
    copy(box2.begin(),box2.end(),ostream_iterator<int>(cout," "));
    cout << endl;
}
void test2()
{
    vector<int> box1 {1,2,3,4,5};
    list<int> box2;

    //结合copy函数，结合迭代器适配器
    // back_insert_iterator<vector<int>> it{box2};
    copy(box1.begin(),box1.end(),back_inserter(box2));

    //打印数据
    copy(box2.begin(),box2.end(),ostream_iterator<int>(cout," "));
    cout << endl;
}
//尾插
void test3()
{
    vector<int> box1 {1,2,3,4,5};
    list<int> box2;

    //结合copy函数，结合迭代器适配器
    //vector中没有push_front
    front_insert_iterator<list<int>> it{box2};
    copy(box1.begin(),box1.end(),it);

    //打印数据
    copy(box2.begin(),box2.end(),ostream_iterator<int>(cout," "));
    cout << endl;
}

//中间插入，使用的是insert函数
void test5()
{
    vector<int> box1 {1,2,3,4,5};
    list<int> box2{6,7,8};

    //结合copy函数，结合迭代器适配器
    //中间插入指定的位置
    auto it = box2.begin();
    ++it;
    copy(box1.begin(),box1.end(),inserter(box2,it));

    copy(box1.begin(),box1.end(),it);

    //打印数据
    copy(box2.begin(),box2.end(),ostream_iterator<int>(cout," "));
    cout << endl;
}

//reverse
void test6()
{
    vector<int> box1{1,2,3,4,5};
    //正着遍历
    //for—each循环
    //简写
    auto it = box1.rbegin();
    //vector<int>::reverse_iterator it = box1.rbegin();  全称
    cout << *it << endl;
    while(it != box1.rend())
    {
        cout << *it << " ";
        //++it实际上是向左移动
        ++it;
    }
    cout << endl;
}
//reverse
void test7()
{
    vector<int> box1{1,2,3,4,5};
    //倒着遍历
    for(auto it = box1.rbegin();it != box1.rend();++it)
    {
        cout << *it << " " ;
    }
    cout << endl;
}

int main(int argc,char *argv[])
{

//    test1();
//    test2();
//    test3();
//    test4();
//    test5();
//    test6();
   test7();
   return 0;
}
