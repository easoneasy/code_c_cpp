#include <iostream>
#include <ostream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <algorithm>
#include <list>
using namespace std;

void test1()
{
    //创建ostream流迭代器
    ostream_iterator<int> it {cout ," "};
    //写数据
    *it = 1;
    ++it;
    *it = 2;
}

void test2()
{
    //创建ostream流迭代器
    //string类型
    ostream_iterator<string> it {cout ," "};
    //写数据
    *it = "abc";
    ++it;
    *it = "hello";
    cout << endl;
}
void test3()
{
    //创建文件输出流对象
    ofstream ofs{"temp.txt"};
    //创建ostream流迭代器
    //string类型
    ostream_iterator<string> it {ofs ,"  "};  //以空格为分隔符
    //写数据
    *it = "abc";
    ++it;
    *it = "hello";
    cout << endl;
    ofs.close();
}

//使用std::copy
void test4()
{
    // vector<int>box {1,2,3,4,5};
    list<int>box {1,2,3,4,5};
    auto itFirst = box.begin();
    auto itLast = box.end();
    //创建ostream流迭代器
    ostream_iterator<int> it {cout ," "};
    //打印容器中的数据
    copy(itFirst,itLast,it);
    //把容器的值，给输出流对象 cout
    cout << endl;
}

int main(int argc,char *argv[])
{

    // test1();
    // test2();
    // test3();
    test4();

    return 0;
}

