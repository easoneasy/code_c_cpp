#include <my_header.h>

int main(int argc,char *argv[])
{
    int fd = open(argv[1],O_RDONLY);
    ERROR_CHECK(fd,-1,"fd open failed.\n");
    struct stat stat_buff;
    fstat(fd,&stat_buff);
    printf("%ld\n",stat_buff.st_size);


    return 0;
}

