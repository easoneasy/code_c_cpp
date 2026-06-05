#include <my_header.h>
void func(int num){
    printf("func num = %d\n",num);
    alarm(1);
}
int main(int argc,char *argv[]){
    signal(SIGALRM,func);
    alarm(5);
    printf("while begin.\n");
    while(1);
    printf("while over.\n");

    return 0;
}

