#include <my_header.h>

int main(int argc,char *argv[])
{
    printf("open 1.pipe begin.\n");
    int fd = open("1.pipe",O_RDONLY);
    printf("open 1.pipe over.\n");
    ERROR_CHECK(fd,-1,"fd open failed.\n");

    fd_set set;
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO,&set);
    FD_SET(fd,&set);
    printf("select begin.\n");
    int ret = select(fd+1,&set,NULL,NULL,NULL);
    printf("select over.ret = %d\n",ret);

    if(FD_ISSET(STDIN_FILENO,&set)){
        printf("stdin enable.\n");
        char buff[100]={0};
        read(STDIN_FILENO,buff,sizeof(buff));
        printf("stdin input : %s \n",buff);
    }
    
    if(FD_ISSET(fd,&set)){
        printf("pipe enable.\n");
        char buff[100]={0};
        read(fd,buff,sizeof(buff));
        printf("pipe msg :%s \n",buff);
    }
    
    close(fd);

    return 0;
}

