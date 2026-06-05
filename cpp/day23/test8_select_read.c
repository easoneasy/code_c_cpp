#include <my_header.h>

int main(int argc,char *argv[])
{
    printf("open 1.pipe begin.\n");
    int write_p = open("1.pipe",O_WRONLY);
    printf("open 1.pipe over.\n");
    ERROR_CHECK(write_p,-1,"open 1.pipe failed.\n");
    
    printf("open 2.pipe begin.\n");
    int read_p = open("2.pipe",O_RDONLY);
    printf("open 2.pipe over.\n");
    ERROR_CHECK(read_p,-1,"open 2.pipe failed.\n");

    while(1){
        fd_set set;
        FD_ZERO(&set);
        FD_SET(read_p,&set);
        FD_SET(STDIN_FILENO,&set);
        
        int ret = select(read_p+1,&set,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&set)){
            printf("stdin enabled.\n");
            char buff1[100]={0};
            ssize_t ret = read(STDIN_FILENO,buff1,sizeof(buff1));
            printf("ret = %ld\n",ret);
            printf("stdin over.\n");
            printf("write begin.\n");
            write(write_p,buff1,ret);
            printf("write over.\n");

        }

        if(FD_ISSET(read_p,&set)){
            printf("read 2.pipe enabled.\n");
            char buff2[100]={0};
            ssize_t count = read(read_p,buff2,sizeof(buff2));
            printf("read 2.pipe over.\n");
            if(count ==0){
                printf("userb closed.\n");
                break;
            }
            printf("msg from userb: %s\n",buff2);
         }
    }
    close(write_p);
    close(read_p);
    return 0;
}

