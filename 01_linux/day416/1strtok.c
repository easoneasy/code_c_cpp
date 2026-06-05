#include <my_header.h>

int main(int argc,char *argv[]){
    char str[]="cd    abc/def/dir";

    char p[100] ={0};
    //提取命令字符
    char *ret =strtok(str," ");
    sprintf(p,"%s",ret);
    printf("%s\n",p);
    while((ret = strtok(NULL,"/"))!= NULL){
        sprintf(p,"%s\n",ret);
    }
    printf("%s\n",p);
    


    return 0;
}

