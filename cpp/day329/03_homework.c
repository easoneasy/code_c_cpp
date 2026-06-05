#include <my_header.h>
void sig_func(int num){
    printf("2 signal func, num = %d\n",num);

    sigset_t set;
    sigemptyset(&set);
    sigpending(&set);
    if(sigismember(&set,3)){
        printf("3 signal is pending.\n");
    }
    sleep(5);
    printf("2 signal function over.\n");
    
}
int main(int argc,char *argv[]){
    struct sigaction act,oldact;
    memset(&act,0,sizeof(act));

    act.sa_handler=sig_func;
    act.sa_flags=SA_RESTART;
    
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask,3);
    act.sa_mask=mask;

    sigaction(2,&act,&oldact);

    while(1);
    return 0;
}

