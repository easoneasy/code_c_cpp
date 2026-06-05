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
    
    char buff1[100]={0};
    recvfrom(lisfd,buff1,100,0,(struct sockaddr *)&client_addr,&len);
    printf("recv:%s\n",buff1);

    sendto(lisfd,"nihao",5,0,(struct sockaddr *)&client_addr,sizeof(client_addr));
    close(lisfd);

    return 0;
}

