#include <my_header.h>

int main(int argc,char *argv[]){
    char *ip = "192.168.254.128";
    char *port ="12345";
    
    int lisfd = socket(AF_INET,SOCK_DGRAM,0);
    
    struct sockaddr_in addr,client_addr;
    socklen_t len = sizeof(client_addr);
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));
    bind(lisfd,(struct sockaddr *)&addr,sizeof(addr));
    
    fd_set set;
    FD_ZERO(&set);
    FD_SET(lisfd,&set);
    FD_SET(STDIN_FILENO,&set);
    while(1){
        fd_set tmp =set;
        select(10,&tmp,NULL,NULL,NULL);
        if(FD_ISSET(lisfd,&tmp)){
            char buff1[100]={0};
            recvfrom(lisfd,buff1,sizeof(buff1),0,(struct sockaddr *)&client_addr,&len);
            printf("recv:%s\n",buff1);
        }
        if(FD_ISSET(STDIN_FILENO,&tmp)){
            char buff[100]={0};
            read(STDIN_FILENO,buff,sizeof(buff));
            int count = sendto(lisfd,buff,strlen(buff),0,(struct sockaddr *)&client_addr,sizeof(client_addr));
            printf("send to client num :%d\n",count);
        }


    }

    close(lisfd);

    return 0;
}

