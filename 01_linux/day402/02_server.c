#include <my_header.h>

int main(int argc,char *argv[]){
    char *ip="192.168.254.128";
    char *port="12345";
    int socket_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socket_fd,-1,"open socket");

    struct sockaddr_in addr,client_addr;
    socklen_t len = sizeof(client_addr);
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));

    int ret = bind(socket_fd,(struct sockaddr *)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");

    ret = listen(socket_fd,10);
    ERROR_CHECK(ret,-1,"listen");

    int conn_fd=accept(socket_fd,(struct sockaddr *)&client_addr,&len);
    ERROR_CHECK(conn_fd,-1,"accept");

    char buff[100]={0};
    int cnt = recv(conn_fd,buff,sizeof(buff),0);
    printf("recv cnt:%d\n",cnt);
    printf("server buff : %s\n",buff);

    cnt = send(conn_fd,"hello",5,0);
    printf("read cnt :%d\n",cnt);

    close(socket_fd);
    close(conn_fd);


    return 0;
}

