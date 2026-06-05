#include <my_header.h>

int main(int argc,char *argv[])
{
    printf("fork before.\n");
    pid_t ret = fork();
    printf("fork after.\n");
    
    printf("ret = %d\n",ret);

    return 0;
}

