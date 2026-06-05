#include <my_header.h>

int main(int argc,char *argv[])
{
    printf("father process pid=%d\n",getpid());
    pid_t ret = fork();
    if(ret == 0){
        printf("child process pid=%d,ppid=%d\n",getpid(),getppid());
    }else{
        printf("father process pid=%d,ppid=%d,child id=%d\n",getpid(),getppid(),ret);
        
    }


    return 0;
}

