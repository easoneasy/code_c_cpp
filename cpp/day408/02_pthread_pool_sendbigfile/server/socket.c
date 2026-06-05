#include <my_header.h>
#include "socket.h"
void init_listen_socket(int *lisfd,char *ip,char *port){
    //创建socket对象，返回监听全连接队列的文件描述符
    *lisfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(*lisfd,-1,"socket");
    //设置端口复用
    int opt=1;
    setsockopt(*lisfd,SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(opt));
    //绑定服务器的ip、端口号
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));
    bind(*lisfd,(struct sockaddr *)&addr,sizeof(addr));
    //监听客户端
    listen(*lisfd,100);

}
