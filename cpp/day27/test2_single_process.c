#include <my_header.h>

int main(int argc,char *argv[])
{
    pid_t fork_ret = fork();
    if(fork_ret==0){
        printf("child process.\n");
        while(1){
            printf("child process is running.\n");
            sleep(1);
        }
    }else{
        printf("father process.\n");
        sleep(5);
        printf("father sleep over.\n");
    }


    return 0;
}

