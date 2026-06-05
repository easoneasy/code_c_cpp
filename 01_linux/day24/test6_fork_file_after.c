#include <my_header.h>

int main(int argc,char *argv[])
{

    pid_t ret =fork();
    if(ret ==0){
        int fd_child = open("file_after.txt",O_RDWR);
        ERROR_CHECK(fd_child,-1,"file open failed.\n");
        write(fd_child,"hello",5);
        sleep(1);
        write(fd_child,"world",5);
    }else{
        int fd_father = open("file_after.txt",O_RDWR);
        ERROR_CHECK(fd_father,-1,"file open failed.\n");
        write(fd_father,"nothing",7);
        sleep(1);
        write(fd_father,"happen",6);
    }


    return 0;
}

