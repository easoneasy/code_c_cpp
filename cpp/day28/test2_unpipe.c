#include <my_header.h>

int main(int argc,char *argv[]){
    int pipe_fd[2]={0};
    int pipe_t = pipe(pipe_fd);
    ERROR_CHECK(pipe_t,-1,"new pipe failed.\n");
    printf("pipe_fd[0]=%d,pipe_fd[1]=%d\n",pipe_fd[0],pipe_fd[1]);

    char buff2[]="hello,how are you today.";
    write(pipe_fd[1],buff2,sizeof(buff2));

    char buff1[50]={0};
    read(pipe_fd[0],buff1,sizeof(buff1));
    printf("msg from pipe:%s  count = %ld\n",buff1,strlen(buff1));

    close(pipe_fd[0]);
    close(pipe_fd[1]);

    return 0;
}

