#include <my_header.h>

typedef  struct con_arr{
    int fd;
    int alive;
}con_t; 
int main(int argc,char *argv[]){
    char *ip = "192.168.254.128";
    char *port = "12345";

    int lisfd=socket(AF_INET,SOCK_STREAM,0);
    int opt=1;
    setsockopt(lisfd,SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(opt));

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
    con_t con_arr[100]={0};
    int size=0;
    while(1){
        fd_set tmp = set;
        int nready = select(10,&tmp,NULL,NULL,NULL);
        printf("%d is ready.\n",nready);
        if(FD_ISSET(lisfd,&tmp)){
            int confd=accept(lisfd,NULL,NULL);
            con_arr[size].fd=confd;
            con_arr[size].alive=1;
            size++;
            FD_SET(confd,&set);
        }
        for(int i =0;i<size;i++){
            int fd=con_arr[i].fd;
            if(FD_ISSET(fd,&tmp)){
                char buff[100]={0};
                int count = recv(fd,buff,sizeof(buff),0);
                if(count ==0){
                    printf("fd = %d client closed.\n",fd);
                    con_arr[i].fd=0;
                    con_arr[i].alive=0;
                    FD_CLR(fd,&set);
                    close(fd);
                    continue;
                }
                printf("recv from client msg : %s\n",buff);
                printf("recv num : %d\n",count);
                for(int j=0;j<size;j++){
                    if(con_arr[j].alive==0||i==j){
                        continue;
                    }
                    send(con_arr[j].fd,buff,sizeof(buff),0);
                }   
            }

        }

    }
    close(lisfd);
    return 0;
}

