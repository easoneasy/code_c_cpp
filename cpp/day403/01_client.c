#include <my_header.h>

int main(int argc,char *argv[]){
    char *ip = "192.168.254.128";
    char *port="12345";

    int lisfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(lisfd,-1,"socket");

    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));

    int ret = connect(lisfd,(struct sockaddr *)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"connect");

    fd_set set;
    FD_ZERO(&set);
    while(1){
        FD_SET(lisfd,&set);
        FD_SET(STDIN_FILENO,&set);
        select(10,&set,NULL,NULL,NULL);
        if(FD_ISSET(lisfd,&set)){
            char buff[100]={0};
            recv(lisfd,buff,sizeof(buff),0);
            printf("msg from server:%s\n",buff);
        }
        if(FD_ISSET(STDIN_FILENO,&set)){
            char buff[100]={0};
            read(STDIN_FILENO,buff,sizeof(buff));
            int count = send(lisfd,buff,strlen(buff),0);
            printf("send to server count : %d\n",count);
        }
    }

    close(lisfd);


    return 0;
}

