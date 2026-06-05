#include <my_header.h>

int main(int argc,char *argv[])
{
    printf("write open begin.\n");
    int write_p =open("1.pipe",O_WRONLY);
    ERROR_CHECK(write_p,-1,"write open failed.\n");
    printf("write open en.\n");

    char buff[4096]={0};
    for(int i=0;i<100;i++){
        printf("write begin.\n");
        ssize_t ret = write(write_p,buff,sizeof(buff));
        printf("round---------%d--------total_num:%ld\n",i,ret);
        printf("write end.\n");
        /* sleep(10); */
    }
    close(write_p);



    return 0;
}

