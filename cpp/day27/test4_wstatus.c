#include <my_header.h>

int main(int argc,char *argv[])
{
    if(fork()==0){
        printf("child process.\n");
        sleep(30);
        printf("child process sleep over.\n");
        return 0;
    }else{
        printf("father process.\n");
        int wstatus;
        pid_t wait_ret = wait(&wstatus);
        printf("father process over.wait ret = %d\n",wait_ret);

        if(WIFEXITED(wstatus)){
            printf("child status : %d\n",WEXITSTATUS(wstatus));
        }else if(WIFSIGNALED(wstatus)){
            printf("child signed:%d\n",WTERMSIG(wstatus));
        }
    }


    return 0;
}

