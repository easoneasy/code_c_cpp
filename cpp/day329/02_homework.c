#include <my_header.h>
void func(int num){
    printf("func begin.\n");
    sleep(4);
    printf("sleep over.\n");
    sigset_t set;
    sigemptyset(&set);
    sigpending(&set);
    if(sigismember(&set,2)){
        printf("2 signal is pending.\n");
    }
}

int main(int argc,char *argv[]){

    signal(2,func);
    printf("while begin.\n");
    while(1);
    printf("while over.\n");

    return 0;
}
