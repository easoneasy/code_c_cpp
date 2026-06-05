#include <my_header.h>

int main(int argc,char *argv[])
{
    mode_t mode =0755;
    int ret=mkdir("test1",mode);
    printf("ret =%d\n",ret);
    ERROR_CHECK(ret,-1,"mkdir failed.\n");


    return 0;
}

