#include <my_header.h>

int main(int argc,char *argv[])
{
    int ret=rmdir("rmdir_test");
    ERROR_CHECK(ret,-1,"rmdir failed.\n");


    return 0;
}

