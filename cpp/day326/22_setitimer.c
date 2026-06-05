#include <my_header.h>
void func(int num){
    printf("num : %d \n",num);
}
int main(int argc,char *argv[]){
    signal(SIGALRM,func);
    struct itimerval new_value;
    new_value.it_interval.tv_sec=1;
    new_value.it_interval.tv_usec=0;

    new_value.it_value.tv_sec=10;
    new_value.it_value.tv_usec=0;

    setitimer(ITIMER_REAL,&new_value,NULL);

    printf("while begin.\n");
    while(1);
    printf("while over.\n");


    return 0;
}

