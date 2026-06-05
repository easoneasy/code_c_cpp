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
    printf("sleep begin.\n");
    sleep(10);
    printf("sleep over.\n");

    sigprocmask(SIG_UNBLOCK,&set,&oldset);

    printf("pause begin.\n");
    pause();
    printf("pause over.\n");

    printf("while begin.\n");
    while(1);

    return 0;
}

