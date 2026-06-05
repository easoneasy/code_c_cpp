#include <iostream>
#include <set>

using namespace std;


void test1()
{
    int n, m;
    // 读取集合 A 和 集合 B 的元素个数
    if (!(cin >> n >> m)) return;

    // 创建一个 set 容器，用来存放并集
    set<int> unionSet;

    int element;
    // 读取集合 A 的所有元素，直接扔进 set
    for (int i = 0; i < n; i++) {
        cin >> element;
        unionSet.insert(element); // set 会自动去重
    }

    // 读取集合 B 的所有元素，同样直接扔进 set
    for (int i = 0; i < m; i++) {
        cin >> element;
        unionSet.insert(element); // 哪怕与 A 冲突，set 也会自动过滤掉
    }

    // 输出最终合并后的集合
    // 因为 set 内部已经自动从小到大排好序了，直接遍历输出即可
    bool isFirst = true;
    for (auto it = unionSet.begin(); it != unionSet.end(); ++it) {
        if (!isFirst) {
            cout << " "; // 保证元素之间用空格隔开，且末尾没有多余空格
        }
        cout << *it;
        isFirst = false;
    }
    cout << endl;
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

