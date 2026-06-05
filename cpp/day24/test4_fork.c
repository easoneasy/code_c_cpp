#include <my_header.h>

int global_num = 100;
int main(int argc,char *argv[])
{
    int num = 10;
    pid_t ret = fork();
    if(ret ==0){
        num = 1;
        global_num =111;
        printf("child process num = %d,global_num=%d\n",num,global_num);
    }else{
        num =2;
        /* global_num =222; */
        printf("father process num = %d,global_num=%d\n",num,global_num);
    }


    return 0;
}

