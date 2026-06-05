#include <my_header.h>

int main(int argc,char *argv[])
{
    mode_t mode = 0775;
    if(argc==3){
        sscanf(argv[2],"%o",&mode);
    }
    char path[1000]={0};
    for(int i=1;i<=30;i++){
        sprintf(path,"%s/test%d",argv[1],i);
        int ret = mkdir(path,mode);
        ERROR_CHECK(ret,-1,"mkdir failed.\n");
    }



    return 0;
}

