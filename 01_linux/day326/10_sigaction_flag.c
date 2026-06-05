#include <my_header.h>
void fun1(int num){
    printf("num=%d\n",num);
}
int main(int argc,char *argv[]){
    struct sigaction act,oldact;
    memset(&act,0,sizeof(act));

    act.sa_handler=fun1;
    act.sa_flags=SA_NODEFER;

    sigaction(2,&act,&oldact);

    printf("while begin.\n");
    while(1);


    return 0;
}

