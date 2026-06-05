#include <my_header.h>
void func(int num){
    printf("num = %d\n",num);
}
int main(int argc,char *argv[]){
    signal(2,func);
    sigset_t set,oldset;
    sigemptyset(&set);
    sigaddset(&set,2);
    sigprocmask(SIG_BLOCK,&set,&oldset);

    sleep(5);
    printf("sleep over.\n");

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask,3);
    printf("sigsuspend begin.\n");
    sigsuspend(&mask);

    printf("while begin.\n");
    while(1);
    printf("while over.\n");


    return 0;
}

