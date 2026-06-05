#include <my_header.h>

int main(int argc,char *argv[])
{
    pid_t ret = fork();
    if(ret == 0){
        printf("child process.\n");
        execl("./test1_caculate","./test1_caculate","3","4",(void *)0);
        printf("child process over.\n");
    }else{
        printf("father process.\n");
        sleep(10);
        printf("father process over.\n");
    }


    return 0;
}

