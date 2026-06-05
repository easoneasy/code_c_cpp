#include <my_header.h>

int main(int argc,char *argv[])
{
    printf("hello wolrd\n");
    close(1);
    int fd=open("222.txt",O_WRONLY);
    printf("fd = %d\n",fd);
    close(fd);


    return 0;
}

