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

    int confd[MAXSIZE];
    for(int i=0;i<MAXSIZE;i++){
        confd[i]=-1;
    }
    fd_set set;
    FD_ZERO(&set);
    FD_SET(listenfd,&set);
    FD_SET(STDIN_FILENO,&set);
    while(1){
        fd_set tmp = set;
        int nready=select(10,&tmp,NULL,NULL,NULL);
        printf("%d is ready.\n",nready);

        if(FD_ISSET(listenfd,&tmp)){
            int new_fd=accept(listenfd,NULL,NULL);
            for(int i=0;i<MAXSIZE;i++){
                if(confd[i]==-1){
                    confd[i]=new_fd;
                    FD_SET(confd[i],&set);
                    break;
                }
            }
        }

        if(FD_ISSET(STDIN_FILENO,&tmp)){
            char buff[100]={0};
            read(STDIN_FILENO,buff,sizeof(buff));
            int count =0;
            for(int i=0;i<MAXSIZE;i++){
                if(confd[i]>0)
                    count = send(confd[i],buff,sizeof(buff),0);
            }
            printf("sent to client num : %d\n",count);
        }
        for(int i=0;i<MAXSIZE;i++){
            if(FD_ISSET(confd[i],&tmp)&&confd[i]>0){
                char buff[100]={0};
                int count=recv(confd[i],buff,sizeof(buff),0);
                if(count ==0){
                    printf("client closed.\n");
                    FD_CLR(confd[i],&set);
                    
                    close(confd[i]);
                    confd[i]=-1;
                }
                printf("recv from client mag:%s\n",buff);
                printf("recv num :%d\n",count);
        }

        }
    }
    close(listenfd);


    return 0;
}

