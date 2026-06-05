#include <my_header.h>
void fun1(int num){
    printf("num : %d\n",num);
    printf("sleep begin.\n");
    sleep(10);
    sigset_t set;
    sigemptyset(&set);
    sigpending(&set);
    if(sigismember(&set,3)){
        printf("3 is inside.\n");
    }else{
        printf("3 not inside.\n");
    }
    printf("sleep over.\n");
}
int main(int argc,char *argv[]){
    struct sigaction act,oldact;
    memset(&act,0,sizeof(act));
    act.sa_handler=fun1;
    
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask,3);
    act.sa_mask=mask;

    sigaction(2,&act,&oldact);
    printf("while begin.\n");
    while(1);
    return 0;
}

