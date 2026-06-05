#include <my_header.h>
void fun(int num){
    printf("num : %d\n",num);
}
int main(int argc,char *argv[]){
    struct sigaction act,oldact;

    memset(&act,0,sizeof(act));

    act.sa_handler=fun;
    sigaction(2,&act,&oldact);
    printf("begin while.\n");
    while(1);


    return 0;
}

