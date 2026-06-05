#include <iostream>
#include <string>
#include <deque>
using namespace std;

//编程题：deque的简单使用
//编写程序，从标准输入读取 string 序列，存入一个 deque 中
//编写一个循环，用迭代器打印 deque 中的元素

void test1()
{
    deque<string> words;
    string input;

    cout << "请输入一系列单词：" << endl;

    // 从标准输入读取 string ，存入 deque 中
    while (cin >> input) {
        words.push_back(input); 
    }

    cout << "\n--- 使用迭代器打印 deque 中的元素 ---" << endl;

    // 循环，用迭代器打印 deque 中的元素
    for (auto it = words.begin(); it != words.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

