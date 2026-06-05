#include <my_header.h>
char *current_find_file(char *path){
    char path_buff[1024]={0};
    sprintf(path_buff,"%s",path);
    char *start = path_buff;
    for(int i=0;i<strlen(path_buff);i++){
        if(path_buff[i]=='/' || path_buff[i]=='\0'){
            path_buff[i]='\0';
            if(*start != '\0'){
                printf("%s\n",start);
            }
            path_buff[i]='/';
            start=path_buff[i+1];
        }
    }
    printf("start : %s \n",start);
}
int main(args,argv[]){
    current_find_file(argv[1]);
    return 0;
}