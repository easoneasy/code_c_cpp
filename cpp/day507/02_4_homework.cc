#include <iostream>
#include <fstream>

using namespace std;


void test1(){
    ifstream ifs{"1.txt"};
    //将文件指针移动到末尾
    ifs.seekg(0,std::ios::end);
    //获取文件指针的位置
    int size = ifs.tellg();
    cout << "size : " << size << endl;
    //创建数组来存储读取的文件的数据
    char buf[size+1];
    buf[size] = 0;
    //将文件指针移动到文件开头
    ifs.seekg(0);
    cout << "pos : " << ifs.tellg() << endl;
    ifs.read(buf,size);
    cout << buf << endl;
    ifs.close();
    

}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

