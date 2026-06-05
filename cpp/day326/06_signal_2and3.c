#include <my_header.h>
void fun1(int num){
    printf("fun1 sleep begin.\n");
    sleep(3);
    printf("fun1 sleep over.\n");
}
void fun2(int num){
    printf("fun2 sleep begin.\n");
    sleep(3);
    printf("fun2 sleep over.\n");
}
int main(int argc,char *argv[]){

    signal(2,fun1);
    signal(3,fun2);
    while(1){
        printf("while is running.\n");
        sleep(1);
    }

    return 0;
}

