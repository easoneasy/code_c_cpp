#include <my_header.h>
void func(int num){
    printf("num : %d\n",num);
}
int main(int argc,char *argv[]){
    pid_t pid = fork();
    if(pid==0){
        printf("child process.\n");
        /* signal(2,func); */
        while(1){
            sleep(1);
            printf("while is running.\n");
        }
    }else{
        printf("father process sleep begin.\n");
        sleep(10);
        kill(pid,2);
    }


    return 0;
}

