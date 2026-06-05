#include <my_header.h>

int main(int argc,char *argv[]){
    struct sockaddr_in addr,client_addr;
    socklen_t len = sizeof(client_addr);
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(argv[1]);
    addr.sin_port=htons(atoi(argv[2]));

    
    int lisfd = socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(lisfd,-1,"socket");

    int opt =1;
    setsockopt(lisfd,SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(opt));
    
    int ret = bind(lisfd,(struct sockaddr *)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");

    ret = listen(lisfd,10);
    ERROR_CHECK(ret,-1,"listen");

    int conn_fd = accept(lisfd,(struct sockaddr *)&client_addr,&len);
    ERROR_CHECK(conn_fd,-1,"accept");

    while(1){
        char buff[100]={0};
        int count = recv(conn_fd,buff,sizeof(buff),0);
        printf("recv from client : %s\n",buff);
        printf("count = %d\n",count);
        
        char buff2[100]={0};
        read(STDIN_FILENO,buff2,sizeof(buff2));
        count = send(conn_fd,buff2,strlen(buff2),0);
        printf("send to client count = %d\n",count);
    }
    close(lisfd);
    close(conn_fd);


    return 0;
}

