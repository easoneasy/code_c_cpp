#include <my_header.h>

int main(int argc,char *argv[])
{
    pid_t ret = fork();
    if(ret == 0){
        printf("child process.\n");
        sleep(10);
        printf("child process over.\n");
    }else{
        printf("father process.\n");
        sleep(2);
        printf("father sleep over.\n");
        pid_t wait_pid = wait(NULL);
        printf("father process over.wait pid = %d\n",wait_pid);
    }


    return 0;
}

