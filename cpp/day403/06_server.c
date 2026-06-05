#include <my_header.h>

int main(int argc,char *argv[]){
    char *ip = "192.168.254.128";
    char *port ="12345";
    
    int lisfd = socket(AF_INET,SOCK_STREAM,0);

    int op =1;
    setsockopt(lisfd,SOL_SOCKET,SO_REUSEADDR,&op,sizeof(op));
    
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));
    bind(lisfd,(struct sockaddr *)&addr,sizeof(addr));

    listen(lisfd,10);

    fd_set set;
    FD_ZERO(&set);
    FD_SET(lisfd,&set);
    int confd=0;
    while(1){
        fd_set tmp =set;
        int ret = select(10,&tmp,NULL,NULL,NULL);
        printf("%d is ready.\n",ret);
        if(FD_ISSET(lisfd,&tmp)){
            confd=accept(lisfd,NULL,NULL);
            FD_SET(confd,&set);
            FD_SET(STDIN_FILENO,&set);
            FD_CLR(lisfd,&set);
        }
        if(FD_ISSET(STDIN_FILENO,&tmp)){
            char buff[100]={0};
            read(STDIN_FILENO,buff,sizeof(buff));
            int count = send(confd,buff,strlen(buff),0);
            printf("send to client %d\n",count);
        }
        if(FD_ISSET(confd,&tmp)){
            char buff[100]={0};
            int ret = recv(confd,buff,sizeof(buff),0);
            if(ret == 0){
                printf("client closed.\n");
                FD_CLR(confd,&set);
                FD_CLR(STDIN_FILENO,&set);
                FD_SET(lisfd,&set);
                close(confd);
                continue;
            }
            printf("recv from client :%s\n",buff);
        }
    }

    close(confd);
    close(lisfd);
    return 0;
}

