#include <iostream>
#include <vector>
#include <string>
using namespace std;
//编程题：vector与string的简单使用
//编写程序，从一个 vector<char> 初始化一个 string

void test1()
{
    //准备一个 vector<char>，里面包含一些字符
    vector<char> char_vec = {'H', 'e', 'l', 'l', 'o', ',', ' ', 'C', '+', '+'};

    // 使用迭代器区间 [begin, end) 初始化 string
    string str(char_vec.begin(), char_vec.end());

    //打印结果，验证转换是否成功
    cout << "Vector 中的字符已成功转换为 string: " << str << endl;
    cout << "String 的长度为: " << str.length() << endl;

}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

