#include <my_header.h>

int main(int argc,char *argv[])
{
    mode_t mode =0777;
    if(argc==3){
        sscanf(argv[2],"%o",&mode);
    }
    char father_path[100]={0};
    for(int i=1;i<=1000;i++){
        sprintf(father_path,"%s/test%d",argv[1],i);
        int ret1=mkdir(father_path,mode);
        ERROR_CHECK(ret1,-1,"mkdir father_path failed.\n");
        chdir(father_path);

        char children_path[100]={0};
        for(int j=1;j<=10;j++){
            sprintf(children_path,"test%d",i*10+j);
            int ret2=mkdir(children_path,mode);
            ERROR_CHECK(ret2,-1,"mkdir children_path failed.\n");
        }
        /* chdir(argv[1]); */
        chdir("../..");
    }


    return 0;
}

