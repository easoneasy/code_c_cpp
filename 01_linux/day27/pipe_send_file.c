#include <my_header.h>

int main(int argc,char *argv[]){
   
    int writep = open("1.pipe",O_WRONLY);
    ERROR_CHECK(writep,-1,"open pipe failed.\n");

    char file_name[]="test1.txt";
    int file_name_len=strlen(file_name);

    write(writep,&file_name_len,sizeof(int));
    write(writep,file_name,file_name_len);

    char file_content[]="hello world!";
    int file_len = sizeof(file_content);
    int str_len = strlen(file_content);
    
    write(writep,&file_len,sizeof(int));
    write(writep,&str_len,sizeof(int));
    write(writep,file_content,str_len);

    close(writep);

    return 0;
}

