#include <my_header.h>

int main(int argc,char *argv[])
{
    pid_t fork_ret = fork();
    if(fork_ret==0){
        printf("child process.\n");
        sleep(30);
        printf("child process over.\n");
    }else{
        printf("father process.\n");
        pid_t wait_pid_ret;
        bool wait_sucess=false;
        for(int i=0;i<60;i++){
            wait_pid_ret = waitpid(fork_ret,NULL,WNOHANG);
            if(wait_pid_ret>0){
                wait_sucess=true;
                break;
            }
            sleep(1);
        }
        printf("father process over.wait_ret = %d\n",wait_pid_ret);
    }


    return 0;
}

