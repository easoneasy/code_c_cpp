#include <my_header.h>
void fun1(int num){
    printf("fun1 sleep begin.\n");
    sleep(2);
    printf("fun1 sleep over.\n");
}
int main(int argc,char *argv[]){
    signal(2,fun1);
    printf("while begin.\n");
    while(1){
        printf("while is running.\n");
    }


    return 0;
}

