#include <iostream>

using namespace std;

/*
    删除器：回收资源
    针对其他资源，文件资源、网络资源...
    需要针对特殊处理的资源进行特殊的回收处理--->自定义删除器
*/
void test1()
{
    FILE *fp = fopen("");
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

