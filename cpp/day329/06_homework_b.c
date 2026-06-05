#include <my_header.h>

int main(int argc,char *argv[]){
    int read_p = open("1.pipe",O_RDONLY);
    int write_p = open("2.pipe",O_WRONLY);
    ERROR_CHECK(read_p,-1,"open 1.pipe failed.\n");
    ERROR_CHECK(write_p,-1,"open 1.pipe failed.\n");

    while(1){

        char buff1[100]={0};
        read(read_p,buff1,sizeof(buff1));
        if(strcmp(buff1,"10")==0){
            return 0;
        }else{
            printf("msg from userb : %s\n",buff1);
        }

        char buff2[100]={0};
        printf("please input your msg:\n");
        read(STDIN_FILENO,buff2,sizeof(buff2));
        if(strcmp(buff2,"1\n")==0){
            write(write_p,"10",2);
            return 0;
        }else{
            write(write_p,buff2,strlen(buff2));
        }

    }

    close(read_p);
    close(write_p);

    return 0;
}
