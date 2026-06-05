#include <my_header.h>

int main(int argc,char *argv[]){
    int write_p = open("1.pipe",O_RDWR);
    ERROR_CHECK(write_p,-1,"write open 1.pipe failed.\n");
    int read_p=open("2.pipe",O_RDONLY);
    ERROR_CHECK(read_p,-1,"read open 2.pipe failed.\n");

    while(1){
        char buff[100]={0};
        printf("please input your msg:\n");
        read(STDIN_FILENO,buff,sizeof(buff));
        if(strcmp(buff,"1\n")==0){
            write(write_p,"10",2);
            return 0;
        }else{
            write(write_p,buff,strlen(buff));
        }

        char buff2[100]={0};
        read(read_p,buff2,sizeof(buff2));
        if(strcmp(buff2,"10")==0){
            return 0;
        }else{
            printf("msg from userb : %s\n",buff);
        }

    }

    close(read_p);
    close(write_p);
    return 0;
}

