#include <my_header.h>
void fun1(int num){
    printf("---------fun1 num=%d------------\n",num);
}
int main(int argc,char *argv[]){
    signal(2,fun1);
    printf("sleep begin.\n");
    unsigned int sleep_ret = sleep(20);
    printf("--------sleep over. sleep ret =%d---------\n",sleep_ret);
    

    return 0;
}

