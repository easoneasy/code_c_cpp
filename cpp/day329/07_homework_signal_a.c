#include <my_header.h>
void signal_fun(int num){
    printf("receive 10 signal.\n");
    exit(0);
}
int main(int argc,char *argv[]){
    int write_p = open("1.pipe",O_RDWR);
    ERROR_CHECK(write_p,-1,"write open 1.pipe failed.\n");
    int read_p=open("2.pipe",O_RDONLY);
    ERROR_CHECK(read_p,-1,"read open 2.pipe failed.\n");
    
    pid_t self_pid=getpid();
    write(write_p,&self_pid,sizeof(pid_t));
    
    pid_t peer_pid;
    read(read_p,&peer_pid,sizeof(pid_t));
    printf("peer pid = %d\n",peer_pid);

    signal(10,signal_fun);
    while(1){
        char buff[100]={0};
        printf("please input your msg:\n");
        read(STDIN_FILENO,buff,sizeof(buff));
        if(strcmp(buff,"1\n")==0){
            kill(peer_pid,10);
            break;
        }else{
            write(write_p,buff,strlen(buff));
        }

        char buff2[100]={0};
        read(read_p,buff2,sizeof(buff2));
        printf("msg from userb : %s\n",buff);

    }

    close(read_p);
    close(write_p);
    return 0;
}

