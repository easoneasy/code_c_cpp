#include <my_header.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    mode_t mode;
    sscanf(argv[2],"%o",&mode);
    int fd = open(argv[1],O_WRONLY | O_CREAT | O_EXCL,mode);
    ERROR_CHECK(fd,-1,"fdopen failed.\n");

    return 0;
}

