#include <my_header.h>

int main(int argc,char *argv[])
{
    printf("hello world\n");
    
    int fd = open("222.txt",O_WRONLY|O_TRUNC);
    write(fd,"12345",5);

    int new_fd=dup(fd);

    write(fd,"67890",5);
    write(new_fd,"abcde",5);
    
    printf("fd = %d\n",fd);
    printf("new_fd=%d\n",new_fd);

    close(fd);
    close(new_fd);

    return 0;
}

