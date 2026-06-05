#include <my_header.h>
void func(int num ,siginfo_t *siginfo,void *p){
    printf("num : %d\n",num);
    printf("func pid :%d\n",getpid());
    printf("xxxpid:%d\n",siginfo->si_pid);
}
int main(int argc,char *argv[]){
    struct sigaction act,oldact;
    memset(&act,0,sizeof(act));
    act.sa_sigaction=func;

    act.sa_flags=SA_SIGINFO;
    sigaction(2,&act,&oldact);

    printf("begin while\n");
    while(1);


    return 0;
}

