#include <my_header.h>

int main(int argc,char *argv[]){
    char *ip="192.168.254.128";
    char *port="12345";
    int socket_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socket_fd,-1,"open socket");

    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));

    int ret = connect(socket_fd,(struct sockaddr *)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"connect");

    while(1){
        char buff1[100]={0};
        read(STDIN_FILENO,buff1,sizeof(buff1));
        int cnt = send(socket_fd,buff1,strlen(buff1),0);
        printf("read cnt :%d\n",cnt);

        char buff[100]={0};
        cnt = recv(socket_fd,buff,sizeof(buff),0);
        printf("recv cnt:%d\n",cnt);
        printf("server buff : %s\n",buff);
    }

    close(socket_fd);


    return 0;
}

