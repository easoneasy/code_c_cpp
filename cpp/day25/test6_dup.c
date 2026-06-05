#include <my_header.h>

int main(int argc,char *argv[])
{
    printf("111111\n");
    int fp = open("2.txt",O_RDWR);
    ERROR_CHECK(fp,-1,"fp open failed.\n");

    int stdout_file = dup(STDOUT_FILENO);
    close(STDOUT_FILENO);
    dup(fp);
    printf("2222222\n");
    close(STDOUT_FILENO);
    dup(stdout_file);
    printf("33333333\n");
    close(STDOUT_FILENO);
    dup(fp);
    printf("44444444\n");
    close(fp);


    return 0;
}

