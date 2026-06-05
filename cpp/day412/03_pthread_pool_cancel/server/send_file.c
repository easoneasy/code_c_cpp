#include <my_header.h>
#include"send_file.h"

void send_diff_file(int fd,char *file_name){
    printf("---------send file begin.------------\n");

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
    printf("---------send file over.------------\n");
}

void send_file(int fd){
    
    printf("-----------send_file ------------\n");
    char *a_file_name="A.txt";
    char *b_file_name="B.txt";

    char recv_buff[20]={0};
    recv(fd,recv_buff,sizeof(recv_buff),MSG_NOSIGNAL);
    //如果接收的数据是A，就发送A.txt
    if(strcmp("A\n",recv_buff)==0){
        send_diff_file(fd,a_file_name);
        printf("A.txt send over.\n");
    }
    //如果接收的数据是B，就发送B.txt
    if(strcmp("B\n",recv_buff)==0){
        send_diff_file(fd,b_file_name);
        printf("B.txt send over.\n");
    }
    
    printf("-----------send_file A.txt------------\n");

}
