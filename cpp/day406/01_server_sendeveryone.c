#include <my_header.h>
#define MAXSIZE 10
int main(int argc,char *argv[]){
    char *ip = "192.168.254.128";
    char *port="12345";

    int listenfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));
    
    bind(listenfd,(struct sockaddr *)&addr,sizeof(addr));

    listen(listenfd,10);
    
    int confd[MAXSIZE]={0};

    fd_set set;
    FD_ZERO(&set);
    FD_SET(listenfd,&set);
    FD_SET(STDIN_FILENO,&set);
    while(1){
        fd_set tmp=set;
        int nready=select(10,&tmp,NULL,NULL,NULL);
        printf("%d ready.\n",nready);
        if(FD_ISSET(listenfd,&tmp)){
            int newfd = accept(listenfd,NULL,NULL);
            for(int i=0;i<MAXSIZE;i++){
                if(confd[i]==0){
                    confd[i]=newfd;
                    FD_SET(confd[i],&set);
                    break;
                }
            }
        }
        for(int i =0;i<MAXSIZE;i++){
            if(confd[i]>0&&FD_ISSET(confd[i],&tmp)){
                char buff[100]={0};
                int count=recv(confd[i],buff,sizeof(buff),0);
                for(int j=0;j!=i&&j<MAXSIZE;j++){
                    send(confd[j],buff,strlen(buff),0);
                    printf("send to client:%d\n",j);
                }
                if(count ==0){
                    printf("client closed.\n");
                    FD_CLR(confd[i],&set);
                    close(confd[i]);
                    continue;
                }
                printf("recv from client :%d\n",count);
                printf("recv num :%d\n",count);
                
            }
        }
        if(FD_ISSET(STDIN_FILENO,&tmp)){
            char buff[100]={0};
            read(STDIN_FILENO,buff,sizeof(buff));
            int count =0;
            for(int i =0;i<MAXSIZE;i++){
                if(confd[i]>0){
                    count = send(confd[i],buff,strlen(buff),0);
                }
            }
            printf("send msg to client num :%d\n",count);
        }
    }
    close(listenfd);

    return 0;
}

