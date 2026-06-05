#include <iostream>
#include <unordered_set>
#include <list>
#include <vector>
#include <deque>
using namespace std;

/*
    迭代器的分类
        1、输出迭代器
            写操作 *it = 100 
        2、输入迭代器
            读操作 *it 
        3、前向迭代器
            只能单向移动，向右移动，++it，不能--
        4、双向迭代器
            可以双向移动，向左向右移动，可以++、--
        5、随机访问迭代器
            上面的功能都有，可以随机访问it += n / it -= n
            功能最强大

*/

//从容器中获取迭代器
//从非关联式容器：unordered_set
//前向迭代器
void test1()
{
    unordered_set<int> box{1,2,3,4,5};
    auto it = box.begin();
    it++;
    // it--;  //error,前向迭代器，只能向右移 
    cout << *it << endl;   //4 ??

}
//从list中获取双向迭代器
void test2()
{
    list<int> box{1,2,3,4,5};
    auto it = box.begin();
    ++it;
    ++it;
    --it;
    //写操作
    *it = 100;
    cout << *it << endl;
    // it += 3;  //error 不支持随机访问
}
//从vector中获取随机访问迭代器
void test3()
{
    vector<int> box{1,2,3,4,5};
    auto it = box.begin();
    ++it;
    ++it;
    --it;
    //写操作
    *it = 100;
    cout << *it << endl;
    //可以随机访问
    it += 3;  
    cout << *it << endl;
    it--;
    cout << *it << endl;
    it--;
}
void test4()
{
    deque<int> box{1,2,3,4};
    box.push_back(0);

}

int main(int argc,char *argv[])
{

    // test1();
    // test2();
    test3();

    return 0;
}

