#include <my_header.h>

int main(int argc,char *argv[]){
    char *ip = "192.168.254.128";
    char *port = "12345";

    int lisfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(lisfd,-1,"socket");

    struct sockaddr_in addr,client_addr;
    socklen_t len = sizeof(client_addr);
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));
    
    int ret = bind(lisfd,(struct sockaddr *)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");

    ret = listen(lisfd,10);
    ERROR_CHECK(ret,-1,"listen");

    int conn_fd = accept(lisfd,(struct sockaddr *)&client_addr,&len);
    ERROR_CHECK(conn_fd,-1,"accept");

    char buff[100]={0};
    int count = recv(conn_fd,buff,sizeof(buff),0);
    ERROR_CHECK(count,-1,"recv");
    printf("data from client : %s\n",buff);
    printf("count = %d\n",count);

    count= send(conn_fd,"hello",5,0);
    ERROR_CHECK(count,-1,"send");
    printf("send to client count :%d\n",count);

    close(lisfd);
    close(conn_fd);

    return 0;
}

