#include <my_header.h>
#include"rm.c"
#include"pwd.c"
//判断命令参数
int is_cmd(char *cmd , char *path){
    while(1){
        char *strarr=(char *)malloc(1024);
        if(strcmp(cmd,"pwd")==0){
            strarr=pwd();
            /* sgend(fd,strarr,strlen(strarr),MSG_NOSIGNAL); */
        }else if (strcmp(cmd,"rm")==0){
            strarr=rm(path);
            printf("%s\n",strarr);
        }
    }
}
int main(int argc,char *argv[]){

    is_cmd(argv[1],argv[2]);

    return 0;
}

