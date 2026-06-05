#include <my_header.h>

int main(int argc,char *argv[]){
    int mkfi_ret = mkfifo("1.pipe",0666);
    ERROR_CHECK(-1,mkfi_ret,"mk pipe failed.\n");

    pid_t fork_ret =  fork();
    if(fork_ret==0){
        printf("child process.\n");
        char buff1[100]={0};
        int readp=open("1.pipe",O_RDONLY);
        ERROR_CHECK(readp,-1,"open pipe failed.\n");
        read(readp,buff1,sizeof(buff1));
        printf("msg from father process : %s\n",buff1);
        close(readp);
    }else{
        printf("father process.\n");
        int writep = open("1.pipe",O_WRONLY);
        char buff2[]="hello this is father process.";
        int write_ret = write(writep,buff2,sizeof(buff2));
        printf("write ret = %d\n",write_ret);
        close(writep);
    }
    return 0;
}

