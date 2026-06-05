#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <string>

// 创建一个 stack<int, list<int>>，依次 push 1,2,3，然后 pop 并输出栈顶元素。

// 创建一个 queue<string, list<string>>，
// 依次 push "a","b","c"，然后 pop 并输出队首元素。 请写出代码并说明输出顺序。

using namespace std;

void test1()
{
    //创建一个底层为list的栈
    stack<int,list<int>> myStack;
    myStack.push(1);
    myStack.push(2);
    myStack.push(3);
    cout << "-------Stack的输出结果--------" << endl;
    while(!myStack.empty())
    {
        //输出当前栈顶元素
        cout << myStack.top() << " " ;
        //弹出栈顶元素
        myStack.pop();
    }
    cout << endl;

    //创建一个底层的list队列
    queue<string,list<string>> myQueue;
    myQueue.push("a");
    myQueue.push("b");
    myQueue.push("c");
    cout << "---------Queue输出结果---------" << endl;
    while(!myQueue.empty())
    {
        cout << myQueue.front() << " " ;
        myQueue.pop();
    }
    cout << endl;

}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

