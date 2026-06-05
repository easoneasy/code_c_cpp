#include <my_header.h>

int main(int argc,char *argv[])
{
    int fd = open("file_before.txt",O_RDWR);
    ERROR_CHECK(fd,-1,"open file failed.\n");

    pid_t ret = fork();
    if(ret == 0){
        write(fd,"hello",5);
        sleep(1);
        write(fd,"world",5);
    }else{
        write(fd,"nothing",7);
        sleep(1);
        write(fd,"happen",6);
    }


    return 0;
}

