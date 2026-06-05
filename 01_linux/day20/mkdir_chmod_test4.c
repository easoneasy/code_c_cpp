#include <my_header.h>

int main(int argc,char *argv[])
{
    mode_t mode=0755;
    if(argc==3){
        //命令行输入的是字符串，用scanf转成8进制
        sscanf(argv[2],"%o",&mode);
    }
    

    int ret=mkdir(argv[1],mode);
    ERROR_CHECK(ret,-1,"mkdir failed.\n");

    return 0;
}

