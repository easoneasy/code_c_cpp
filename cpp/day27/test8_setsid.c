#include <my_header.h>

int main(int argc,char *argv[])
{
    if(fork()==0){
        printf("child process begin.\n");
        setsid();
        while(1){
            printf("child process running.pid=%d,getpgrp=%d,getsid=%d\n",
                   getpid(),getpgrp(),getsid(0));
            sleep(1);
        }
    }else{
        printf("father process begin.\n");
        sleep(20);
        printf("father process over.\n");
        printf("child process running.pid=%d,getpgrp=%d,getsid=%d\n",
                   getpid(),getpgrp(),getsid(0));
    }


    return 0;
}

