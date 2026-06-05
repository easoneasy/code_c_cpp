#include <my_header.h>
#include"socket.h"


void init_socket(int *fd,char *ip,char *port){
    *fd=socket(AF_INET,SOCK_STREAM,0);

    int opt=1;
    setsockopt(*fd,SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(opt));
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));

    bind(*fd,(struct sockaddr *)&addr,sizeof(addr));

    listen(*fd,100);
}






