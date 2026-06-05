#include <my_header.h>

int main(int argc,char *argv[])
{
    int read_p =open("1.pipe",O_RDONLY);
    ERROR_CHECK(read_p,-1,"read open failed.\n");

    char buff[4096]={0};
    for(int i=0;i<100;i++){
        printf("read begin.\n");
        ssize_t ret = read(read_p,buff,sizeof(buff));
        printf("round---------%d--------total_num:%ld\n",i,ret);
        printf("read end.\n");
    }
    close(read_p);



    return 0;
}

