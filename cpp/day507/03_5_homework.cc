#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void test1(){
    string input;
    int result;
    while(1)
    {
        cout << "请输入数字：" << endl;
        //从键盘输入，放入字符串input中
        getline(cin,input);
        //创建对象
        istringstream iss{input};
        //将对象中的数据放入result中
        if(iss >> result)
        {
            char remain;
            if(iss >> remain)
            {
                cout << "请输入数字，含有非法字符" << endl;
            }else{
                return;
            }
        }else{
            cout << "请输入数字，不是有效的整数" << endl;
        }

    }
}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

