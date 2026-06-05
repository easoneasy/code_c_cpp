#include <my_header.h>

int main(int argc,char *argv[]){
    int pipe_fd[2]={0};
    int pipe_p = pipe(pipe_fd);
    ERROR_CHECK(pipe_p,-1,"create pipe failed.\n");
    pid_t fork_ret = fork();
    if(fork_ret==0){
        printf("child process.\n");
        close(pipe_fd[1]);
        char buff1[100]={0};
        read(pipe_fd[0],buff1,sizeof(buff1));
        printf("msg from father peocess:%s\n",buff1);
        close(pipe_fd[0]);
        }else{
           printf("father process.\n");
           close(pipe_fd[0]);
           char buff2[]="Hello,This is father peocess.";
           write(pipe_fd[1],buff2,sizeof(buff2));
           printf("write pipe over.\n");
           close(pipe_fd[1]);
           
        }


    return 0;
}

