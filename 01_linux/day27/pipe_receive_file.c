#include <my_header.h>

int main(int argc,char *argv[]){
    int readp=open("1.pipe",O_RDONLY);
    ERROR_CHECK(readp,-1,"pipe open failed.\n");

    int file_name_len=0;
    read(readp,&file_name_len,sizeof(int));
    char file_name[10]={0};
    read(readp,file_name,file_name_len);
    
    int file_len=0;
    read(readp,&file_len,sizeof(int));
    int str_len=0;
    read(readp,&str_len,sizeof(int));
    char file_content[100]={0};
    read(readp,file_content,str_len);

    mkdir("files",0777);
    chdir("files");

    int new_fd = open(file_name,O_RDWR|O_CREAT,0666);
    ftruncate(new_fd,file_len);
    write(new_fd,file_content,str_len);
    close(readp);
    close(new_fd);

    return 0;
}

