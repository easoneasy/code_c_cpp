#include <my_header.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDONLY);
    ERROR_CHECK(fd,-1,"fd open failed.\n");

    char buff[10]={0};
    ssize_t ret = read(fd,buff,sizeof(buff));
    printf("ret = %ld\n",ret);
    printf("----%s----\n",buff);
    
    
    ssize_t ret2 = read(fd,buff,sizeof(buff));
    printf("ret2 = %ld\n",ret2);
    printf("----%s----\n",buff);

    close(fd);
    return 0;
}

