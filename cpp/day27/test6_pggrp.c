#include <my_header.h>

int main(int argc,char *argv[])
{
    printf("pid = %d,pgrp = %d\n",getpid(),getpgrp());

    if(fork()==0){
        setpgid(0,0);
        printf("child process pid = %d,pgrp = %d\n",getpid(),getpgrp());
    }else{
        printf("father process pid = %d,pgrp = %d\n",getpid(),getpgrp());

    }


    return 0;
}

