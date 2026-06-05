#include <iostream>
#include <stack>
#include <vector>
#include <list>
#include <queue>
using namespace std;

/*
    容器适配器
    1、stack
        默认使用deque
    2、queue
        默认底层使用deque
    3、priority_queue   //优先级队列 
        默认使用vector，std::less，默认使用升序排序
        
*/


//stack
void test1()
{
    //默认底层使用deque
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    //遍历结束后，栈空
    while(!s.empty())
    {
        cout << s.top() << endl;
        s.pop();     //出栈操作
    }
    cout << s.top() << endl;
}
//stack
void test2()
{
    //指定底层实现vector
    stack<int,vector<int>> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    //遍历结束后，栈空
    while(!s.empty())
    {
        cout << s.top() << endl;
        s.pop();     //出栈操作
    }
    cout << s.top() << endl;
}

//stack
void test3()
{
    //指定底层实现list
    stack<int,list<int>> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    //遍历结束后，栈空
    while(!s.empty())
    {
        cout << s.top() << endl;
        s.pop();     //出栈操作
    }
    cout << s.top() << endl;
}

//queue
void test4()
{
    //默认底层是queue
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    while(!q.empty())
    {
        cout << q.front() << endl;
        q.pop();     //出栈操作
    }
    cout << q.front() << endl;

}
//priority_queue
void test5()
{
    //默认底层是vector
    priority_queue<int> q;
    q.push(2);
    q.push(4);
    q.push(1);
    q.push(3);
    //出栈的时候大的数先出栈  less
    while(!q.empty())
    {
        cout << q.top() << endl;
        q.pop();     //出栈操作
    }
}
//priority_queue
void test6()
{
    //修改底层实现为deque，注意不能使用list，原因是list的迭代器不适配
    priority_queue<int,deque<int>,greater<int>> q;
    q.push(2);
    q.push(4);
    q.push(1);
    q.push(3);
    //出栈的时候小的数先出栈  greater
    while(!q.empty())
    {
        cout << q.top() << endl;
        q.pop();     //出栈操作
    }
}

int main(int argc,char *argv[])
{

    // test1();
    // test2();
    // test3();
    test6();

    return 0;
}

