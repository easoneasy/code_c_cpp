#include <my_header.h>

int main(int argc,char *argv[])
{
    printf("1a\n");
    fork();
    printf("2a\n");
    fork();
    printf("3a\n");


    return 0;
}

