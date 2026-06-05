#include <my_header.h>

int main(int argc,char *argv[])
{
    printf("fork before.\n");
    pid_t ret = fork();
    if(ret ==0){
        printf("child process pid =%d,ret=%d",getpid(),ret);
    }else{
        printf("father process pid=%d,ret=%d",getpid(),ret);
    }


    return 0;
}

