#include <iostream>
using namespace std;

void test1(){
    string str{"abcdef"};
    //打印第一个字符
    cout << str.at(0) << endl;
    //迭代器
    auto it = str.begin();
    ++it;
    cout << *it << endl;
    auto it1 = str.end();
    --it1;
    cout << *it1 << endl;
    //遍历字符串
    for(auto & element : str)
    {
        cout << element;
    }
    cout << endl;

    //输出容量、大小
    cout << str.size() << endl;
    cout << str.capacity() << endl;

}

int main(int argc,char *argv[])
{
    test1();
    return 0;
}
