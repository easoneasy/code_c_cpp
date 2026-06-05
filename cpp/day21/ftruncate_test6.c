#include <my_header.h>

int main(int argc,char *argv[])
{
    int fd=open("1.txt",O_RDONLY);
    ftruncate(fd,100);

    //在下载场景中使用，用来占位
    //防止下载过程中空间被别的数据占用


    return 0;
}

