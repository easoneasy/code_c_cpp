#include <my_header.h>

int main(int argc,char *argv[])
{
    int read_p=open("1.pipe",O_RDONLY);
    ERROR_CHECK(read_p,-1,"read open failed.\n");
    
    printf("read begin.\n");
    char buff[100]={0};
    ssize_t ret=read(read_p,buff,sizeof(buff));
    printf("read over.\n");
    printf("ret = %ld\n",ret);
    printf("recieve msg : %s\n",buff);
    
    close(read_p);
    return 0;
}

