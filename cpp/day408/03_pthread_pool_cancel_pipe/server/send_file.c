#include <my_header.h>
#include"send_file.h"

void send_file(int fd){
    
    printf("-----------send_file ------------\n");
    /* send(fd,"hello",5,0); */
    char *file_name="1.txt";
    //打开文件，获取文件描述符
    int file_fd=open(file_name,O_RDONLY);
    
    //获取文件的大小
    struct stat stat_buff;
    fstat(file_fd,&stat_buff);
    off_t file_len = stat_buff.st_size;
    //发送文件名长度
    int file_name_len = strlen(file_name);
    send(fd,&file_name_len,sizeof(int),MSG_NOSIGNAL);
    //发送文件名
    send(fd,file_name,file_name_len,MSG_NOSIGNAL);

    //发送文件长度
    send(fd,&file_len,sizeof(off_t),MSG_NOSIGNAL);
    //发送文件
    sendfile(fd,file_fd,NULL,file_len);

    printf("---------send_file over.--------\n");

}
