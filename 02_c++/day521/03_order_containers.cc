#include <iostream>
#include <array>
#include <forward_list>
#include <vector>

using namespace std;

/*
    容器分类：
    1、顺序容器
        array ：静态数组
        vector：动态数组
        forward_list ：单链表
        list：双向链表
        deque：双向队列
    2、关联容器：底层实现是红黑树
        set  
        map
        multimap
        multiset
    3、无序关联式容器：底层实现是哈希表
        unordered_set
        unordered_map
        unordered_multimap
        unordered_multiset
*/

//了解 array 、 forward_list
void test1()
{
    array<int,5> arr {1,2,3,4,5};
    cout << arr[0] << endl;
    cout << arr.at(1) << endl;
    cout << arr.front() << endl;
    cout << arr.back() << endl;

    cout << "---------------" << endl;
    forward_list<int> fl {4,5,6};
    cout << fl.front() << endl;
    for(auto &e : fl)
    {
        cout << e << " " ;
    }
    cout << endl;

}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

