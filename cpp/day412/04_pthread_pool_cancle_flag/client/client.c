#include <my_header.h>

int main(int argc, char *argv[])
{
    char *ip = "192.168.254.128";
    char *port = "12345";

    //创建文件描述符
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(listen_fd, -1, "socket");

    //绑定服务器的ip与端口号
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));//初始化addr

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);//本机字节序转换为网络字节序
    addr.sin_port = htons(atoi(port));

    //调用connect函数进行三次握手
    int ret = connect(listen_fd, (struct sockaddr *)&addr, sizeof(addr));
    ERROR_CHECK(ret, -1, "connect");

    //发送A/B
    printf("please input your need file\n");
    char choice_buff[10]={0};
    read(STDIN_FILENO,choice_buff,sizeof(choice_buff));
    send(listen_fd,choice_buff,strlen(choice_buff),MSG_WAITALL);
    printf("your need file is %s\n",choice_buff);


    //------------------------------------------------------
    //接收大文件
    
    //接收文件名大小
    int file_name_len=0;
    recv(listen_fd,&file_name_len,sizeof(int),MSG_WAITALL);
    //接收文件名
    char file_name[10]={0};
    recv(listen_fd,file_name,file_name_len,MSG_WAITALL);
    //接收文件大小
    off_t file_len = 0;
    recv(listen_fd,&file_len,sizeof(off_t),MSG_WAITALL);
    int file_fd=open(file_name,O_RDWR|O_CREAT,0600);
    //为文件占空间
    ftruncate(file_fd,file_len);
    //内存映射
    char *p = (char *)mmap(NULL,file_len,PROT_READ|PROT_WRITE,MAP_SHARED,file_fd,0);
    /* ERROR_CHECK(*p,-1,"mmap"); */
    off_t total_recv=0;
    while(total_recv<file_len){
        ssize_t ret =recv(listen_fd,p+total_recv,file_len-total_recv,0);
        if(ret<=0){
            break;
        }
        total_recv +=ret;
    }
    printf("recv total :%ld\n",total_recv);
    //接收文件
    /* recv(listen_fd,p,file_len,MSG_WAITALL); */
    //解除内存映射
    munmap(p,file_len);

    close(file_fd);
    close(listen_fd);
    return 0;
}


