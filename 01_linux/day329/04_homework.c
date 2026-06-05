#include <my_header.h>
void func(int num){
    printf("2 signal num = %d\n",num);
    sleep(3);
    printf("2 signal sleep over.\n");
}
int main(int argc,char *argv[]){
    struct sigaction act,oldact;
    act.sa_handler=func;
    act.sa_flags=SA_RESTART;

    sigset_t block_set;
    sigemptyset(&block_set);
    sigaddset(&block_set,2);
    
    sigaction(2,&act,&oldact);
    sigprocmask(SIG_BLOCK,&block_set,NULL);
    
    sleep(5);
    sigset_t set;
    sigemptyset(&set);
    sigpending(&set);
    if(sigismember(&set,2)){
        printf("2 signal is pending.\n");
    }
    
    sigprocmask(SIG_UNBLOCK,&set,NULL);
    while(1);
    return 0;
}

