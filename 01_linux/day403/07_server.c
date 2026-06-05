#include <my_header.h>
#define MAXSIZE 10
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


    //存10个客户端
    int confd[MAXSIZE];
    for(int i=0;i<MAXSIZE;i++){
        confd[i]=-1;
    }
    while(1){
        fd_set set;
        FD_ZERO(&set);
        FD_SET(lisfd,&set);
        for(int i=0;i<MAXSIZE;i++){
            if(confd[i]>0){
                FD_SET(confd[i],&set);
            }
        }
        fd_set tmp =set;
        int ret = select(10,&tmp,NULL,NULL,NULL);
        printf("%d is ready.\n",ret);
        if(FD_ISSET(lisfd,&tmp)){
            //把新加入全连接的文件描述符加入存放文件描述符的数组中
            int new_fd =accept(lisfd,NULL,NULL);
            for(int i=0;i<MAXSIZE;i++){
                if(confd[i]==-1){
                    confd[i]=new_fd;
                    break;
                }
                FD_SET(confd[i],&set);
            }
            FD_SET(STDIN_FILENO,&set);
        }
        if(FD_ISSET(STDIN_FILENO,&tmp)){
            char buff[100]={0};
            read(STDIN_FILENO,buff,sizeof(buff));
            //发送给所有客户端
            for(int i=0;i<MAXSIZE;i++){
                if(confd[i]>0){
                    int count = send(confd[i],buff,strlen(buff),0);
                    printf("send to client %d\n",count);
                }
            }
        }
        for(int i=0;i<MAXSIZE;i++){
            if(confd[i]>0 && FD_ISSET(confd[i],&tmp)){
                char buff[100]={0};
                int ret = recv(confd[i],buff,sizeof(buff),0);
                if(ret == 0){
                    printf("client closed.\n");
                    FD_CLR(confd[i],&set);
                    FD_CLR(STDIN_FILENO,&set);
                    FD_SET(lisfd,&set);
                    close(confd[i]);
                    continue;
                }
                printf("recv from client :%s\n",buff);
            }
        }
    }
    close(lisfd);
    return 0;
}

