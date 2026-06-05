#include <my_header.h>

int main(int argc,char *argv[])
{
    if(fork()==0){
        printf("child process, pid = %d,sid=%d\n",getpid(),getsid(0));
        sleep(10);
        printf("child sleep over.\n");
    }else{
        printf("father process, pid = %d,sid=%d\n",getpid(),getsid(0));
        sleep(10);
        printf("father sleep over.\n");
    }


    return 0;
}

