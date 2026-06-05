#include <my_header.h>

int main(int argc,char *argv[])
{
    printf("open read begin.\n");
    int read_p =open("1.pipe",O_RDONLY);
    ERROR_CHECK(read_p,-1,"read open failed.\n");
    printf("open read over.\n");

    char buff[4096]={0};
    for(int i=0;i<100;i++){
        printf("read begin.\n");
        ssize_t ret = read(read_p,buff,sizeof(buff));
        printf("round---------%d--------total_num:%ld\n",i,ret);
        printf("read end.\n");
        sleep(5);
    }
    close(read_p);

    return 0;
}

