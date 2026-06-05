#include <my_header.h>
void fun1(int num){
    printf("fun1 sleep begin.\n");
    sleep(10);
    printf("fun1 sleep over.\n");
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

