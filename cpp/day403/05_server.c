#include <my_header.h>

int main(int argc,char *argv[]){
    char *ip = "192.168.254.128";
    char *port = "12345";
    //创建文件描述符
    int lisfd = socket(AF_INET,SOCK_STREAM,0);
    //绑定服务器ip与端口号
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));

    bind(lisfd,(struct sockaddr *)&addr,sizeof(addr));
    //设置端口重用
    int op =1;
    setsockopt(lisfd,SOL_SOCKET,SO_REUSEADDR,&op,sizeof(op));
    //监听
    listen(lisfd,10);
    printf("server is listening.\n");

    //定义位图变量
    fd_set set;
    FD_ZERO(&set);
    //监听文件描述符，文件描述符可读则取连接
    FD_SET(lisfd,&set);
    int confd=0;
    while(1){
        //创建临时位图，防止更改传入之前的位图
        fd_set tmp = set;
        select(10,&tmp,NULL,NULL,NULL);
        if(FD_ISSET(lisfd,&tmp)){
            confd=accept(lisfd,NULL,NULL);
            FD_SET(confd,&set);
            FD_SET(STDIN_FILENO,&set);
            FD_CLR(lisfd,&set);
        }
        if(FD_ISSET(STDIN_FILENO,&tmp)){
            // printf("please input your msg\n");
            char buff[100]={0};
            read(STDIN_FILENO,buff,sizeof(buff));
            int count = send(confd,buff,strlen(buff),0);
            printf("send to client num : %d\n",count);
        }
        if(FD_ISSET(confd,&tmp)){
            char buff[100]={0};
            int count = recv(confd,buff,sizeof(buff),0);
            if(count == 0){
                printf("client closed.\n");
                FD_CLR(STDIN_FILENO,&set);
                FD_CLR(confd,&set);
                FD_SET(lisfd,&set);
                close(confd);
            }
            printf("recv msg from client :%s\n",buff);
            printf("recv num :%d\n",count);

        }

    }

    close(confd);
    close(lisfd);

    return 0;
}

