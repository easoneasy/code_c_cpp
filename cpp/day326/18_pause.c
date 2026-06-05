#include <my_header.h>
void func(int num){
    printf("num : %d\n",num);
}
int main(int argc,char *argv[]){
    struct sigaction act,oldact;
    memset(&act,0,sizeof(act));
    act.sa_handler=func;
    sigaction(2,&act,&oldact);

    printf("pause begin.\n");
    pause();
    printf("pause over.\n");
    printf("while begin.\n");
    while(1);

    return 0;
}

