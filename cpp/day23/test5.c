#include <my_header.h>

int main(int argc,char *argv[])
{
    printf("open begin.\n");
    int fd = open("1.pipe",O_RDWR);
    printf("open over.\n");

    char buff[]="hello! How are you today?";

    printf("write begin.---------------\n");
    write(fd,buff,sizeof(buff));
    printf("write over.----------------\n");

    printf("read begin.----------------\n");
    int ret = read(fd,buff,sizeof(buff));
    printf("read msg : %s\n",buff);
    printf("ret = %d\n",ret);
    printf("read over-----------------.\n");
    
    close(fd);

    return 0;
}

