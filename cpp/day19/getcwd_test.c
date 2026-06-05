#include <my_header.h>

int main(int argc,char *argv[])
{
    char path[20]={0};
    char *p=getcwd(path,sizeof(path));
    //存放当前工作目录字符串的字符数组,数组大小
    ERROR_CHECK(p,NULL,"getwd");
    printf("cwd=%s\n",path); //打印当前工作目录的路径

    return 0;
}

