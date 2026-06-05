#include <my_header.h>
void fun1(int num){
    printf("----------fun1 num1 = %d--------\n",num);
}
void fun2(int num){
    printf("----------fun2 num2 = %d--------\n",num);
}
int main(int argc,char *argv[]){
    signal(2,fun1);
    signal(3,fun2);
    printf("sleep begin.\n");
    sleep(10);
    printf("sleep over.\n");
    while(1){
        printf("while is runing.\n");
        sleep(2);
    }


    return 0;
}

