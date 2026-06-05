#include <my_header.h>

int main(int argc,char *argv[])
{
    printf("read open 1.pipe begin.\n");
    int read_p = open("1.pipe",O_RDONLY);
    printf("read open 1.pipe over.\n");
    
    printf("write open 2.pipe begin.\n");
    int write_p = open("2.pipe",O_WRONLY);
    printf("write open 2.pipe over.\n");
    ERROR_CHECK(read_p,-1,"read_p open failed.\n");
    ERROR_CHECK(write_p,-1,"write_p open failed.\n");

    while(1){
        char buff1[100]={0};
        printf("read begin.\n");
        read(read_p,buff1,sizeof(buff1));
        printf("msg from userb : %s",buff1);
        printf("read over.\n");

        char buff2[100]={0};
        printf("please input write content.\n");
        ssize_t ret =read(STDIN_FILENO,buff2,sizeof(buff2));
        printf("write begin.\n");
        write(write_p,buff2,sizeof(buff2));
        printf("write nums : %ld\n",ret);
        printf("write over.\n");
    }

    close(read_p);
    close(write_p);

    return 0;
}

