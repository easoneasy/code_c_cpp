#include <my_header.h>
void fun1(int num){
    printf("fun1 num = %d\n",num);
}
int main(int argc,char *argv[]){
    signal(2,fun1);
    printf("read begin.\n");
    char buff[100]={0};
    read(STDIN_FILENO,buff,sizeof(buff));
    printf("read over.\n");

    return 0;
}

