#include <my_header.h>
void fun1(int num){
    printf("----------fun1 num:%d----------\n",num);
}
void fun2(int num){
    printf("----------fun2 num:%d----------\n",num);
}
int main(int argc,char *argv[]){
    signal(2,fun1);
    printf("sleep begin.\n");
    sleep(10);
    printf("sleep over.\n");
    signal(2,fun2);
    
    while(1){
        printf("while is running.\n");
        sleep(2);
    }

    return 0;
}

