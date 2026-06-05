#include <my_header.h>

int main(int argc,char *argv[])
{
    pid_t fork_ret = fork();
    if(fork_ret == 0){
        printf("child process begin.\n");
        sleep(20);
        printf("child process over.\n");
    }else{
        printf("father process begin.\n");
        pid_t waitpid_ret = waitpid(fork_ret,NULL,WNOHANG);
        printf("wait over,ret = %d\n",waitpid_ret);
        printf("child process over.\n");
    }


    return 0;
}

