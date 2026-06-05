#include <my_header.h>

int main(int argc,char *argv[])
{
    pid_t ret = fork();
    if(ret == 0){
        printf("child process.\n");
        sleep(3);
        printf("child process over.\n");
    }else{
        printf("father process.\n");
        while(1){
            printf("father process is running.\n");
            sleep(2);
        }
    }


    return 0;
}

