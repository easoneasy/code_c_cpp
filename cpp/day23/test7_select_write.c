#include <my_header.h>

int main(int argc,char *argv[])
{
    printf("open 1.pipe begin.\n");
    int fd=open("1.pipe",O_WRONLY);
    printf("open 1.pipe over.\n");
    ERROR_CHECK(fd,-1,"open 1.pipe failed.\n");

    sleep(30);
    char buff[]="hello user A , How are you today?";
    printf("write begin.\n");
    write(fd,buff,sizeof(buff));
    printf("write over.\n");
    sleep(5);

    close(fd);

    return 0;
}

