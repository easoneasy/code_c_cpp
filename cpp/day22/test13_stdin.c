#include <my_header.h>

int main(int argc,char *argv[])
{
    close(STDIN_FILENO);

    int fd = open("222.txt", O_RDONLY);

    printf("fd = %d\n", fd);


    int num1 = 0;
    double d1 = 0.0;

    scanf("%d %lf", &num1, &d1);

    printf("num1 = %d\n d1 = %lf\n", num1, d1);


    return 0;
}

