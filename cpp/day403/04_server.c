#include <my_header.h>

int main(int argc,char *argv[]){
    char *ip = "192.168.254.128";
    char *port="12345";

    int lisfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(lisfd,-1,"socket");

    struct sockaddr_in addr,client_addr;
    socklen_t len = sizeof(client_addr);
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));

    int opt =1;
    setsockopt(lisfd,SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(opt));
    int ret = bind(lisfd,(struct sockaddr *)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");

    ret = listen(lisfd,10);
    ERROR_CHECK(ret,-1,"listen");

    int con_fd=0;
    fd_set set;
    while(1){
        FD_ZERO(&set);
        FD_SET(lisfd,&set);
        /* fd_set tmp =set; */
        con_fd=accept(lisfd,(struct sockaddr *)&client_addr,&len);
        ERROR_CHECK(con_fd,-1,"accept");
        FD_SET(con_fd,&set);
        FD_SET(STDIN_FILENO,&set);
        select(10,&set,NULL,NULL,NULL);
        if(FD_ISSET(con_fd,&set)){
            char buff[100]={0};
            int count = recv(con_fd,buff,sizeof(buff),0);
            if(count ==0){
                printf("client closed.\n");
                close(con_fd);
            }
            printf("msg from client:%s\n",buff);
        }
        if(FD_ISSET(STDIN_FILENO,&set)){
            char buff[100]={0};
            read(STDIN_FILENO,buff,sizeof(buff));
            int count = send(con_fd,buff,strlen(buff),0);
            printf("send to client count : %d\n",count);
        }
    }

    close(lisfd);
    close(con_fd);


    return 0;
}

