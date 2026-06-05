#include <iostream>
#include <ostream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <algorithm>
#include <list>
#include <vector>

using namespace std;

/*
    输入流迭代器 istream_iterator
        无参构造函数：构造流尾迭代器
*/

void test1()
{
    //创建istream流迭代器
    istream_iterator<int> it {cin};
    //读数据
    int num1;
    int num2;
    num1 = *it;
    ++it;
    num2 = *it;
    cout << "-----cout------" << endl;
    cout << num1 << endl;
    cout << num2 << endl;

}
void test2()
{
    //创建istream流迭代器
    istream_iterator<string> it {cin};
    //读数据
    string str1;
    string str2;
    str1 = *it;
    ++it;
    str2 = *it;
    cout << "-----cout------" << endl;
    cout << str1 << endl;
    cout << str2 << endl;

}

//通过键盘输入数据，填充到容器中
void test3()
{
    vector<int> box{};
    //创建输入流迭代器对象作为first
    istream_iterator<int> itFirst{cin};
    //创建输入流迭代器对象作为last
    //使用istream_iterator的无参构造函数创建的对象作为流的末尾
    istream_iterator<int> itLast{};
    //使用copy实现
    ostream_iterator<int> os{cout," "};
    // copy(itFirst,itLast,box.begin()); //error //容器中没有数据，box.begin是空指针

    cout << "-------------" << endl;
    //使用迭代器适配器
    //创建一个尾插的迭代器适配器对象
    back_insert_iterator it {box};
    //可以用back_insert函数来简化操作

    
    //直接调用函数，不用创建对象
    copy(itFirst,itLast,back_inserter(box));
    copy(itFirst,itLast,it);  //放入it中
    cout << "------------" << endl;
    cout << box.size() << endl;
    //打印box的数据，输出到终端
    copy(box.begin(),box.end(),os);
}
int main(int argc,char *argv[])
{

    // test1();
    // test2();
    test3();

    return 0;
}

