#include <my_header.h>

int main(int argc,char *argv[]){
    int pipe1_fd [2]={0};
    int pipe2_fd [2]={0};
    int p1 = pipe(pipe1_fd);
    int p2 = pipe(pipe2_fd);
    ERROR_CHECK(p1,-1,"pipe1 create failed.\n");
    ERROR_CHECK(p2,-1,"pipe2 create failed.\n");
    
    int fork_ret = fork();
    if(fork_ret == 0){
        printf("child process.\n");
        close(pipe1_fd[0]);
        close(pipe2_fd[1]);

        char buff1[100]={0};
        read(pipe2_fd[0],buff1,sizeof(buff1));
        printf("msg from father:%s\n",buff1);

        char msg[]="Hello, this is child process.";
        write(pipe1_fd[1],msg,sizeof(msg));
        printf("child msg send success.\n");
    }else{
        printf("father process.\n");
        close(pipe1_fd[1]);
        close(pipe2_fd[0]);

        char msg[]="Hello, this is father process.";
        write(pipe2_fd[1],msg,sizeof(msg));
        printf("father msg send success.\n");

        char buff1[100]={0};
        read(pipe1_fd[0],buff1,sizeof(buff1));
        printf("msg from father:%s\n",buff1);
    }
    return 0;
}

