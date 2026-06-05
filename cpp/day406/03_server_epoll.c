#include <my_header.h>
void add_epoll_fd(int epfd,int fd){
    struct epoll_event evt;
    evt.events=EPOLLIN;
    evt.data.fd=epfd;
    
    int ret = epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&evt);
    ERROR_CHECK(ret,-1,"add_epoll_fd");
}
void del_epoll_fd(int epfd,int fd){
    struct epoll_event evt;
    evt.events=EPOLLIN;
    evt.data.fd=fd;
    int ret = epoll_ctl(epfd,EPOLL_CTL_DEL,fd,&evt);
    ERROR_CHECK(ret,-1,"del_epoll_fd");
}
int main(int argc,char *argv[]){
    char *ip ="192.168.254.128";
    char *port ="12345";

    int lisfd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(atoi(port));

    bind(lisfd,(struct sockaddr *)&addr,sizeof(addr));

    listen(lisfd,10);

    int epfd=epoll_create(1);
    ERROR_CHECK(epfd,-1,"epoll_create");

    struct epoll_event evt;
    evt.events=EPOLLIN;
    evt.data.fd=lisfd;
    int ret = epoll_ctl(epfd,EPOLL_CTL_ADD,lisfd,&evt);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    
    int conn_fd=0;
    while(1){
        struct epoll_event lst[10];

        int nready = epoll_wait(epfd,lst,10,-1);
        ERROR_CHECK(nready,-1,"epoll_wait");
        printf("nready : %d\n",nready);
        for(int i=0;i<nready;i++){
            int fd=lst[i].data.fd;
            if(fd==lisfd){
                conn_fd=accept(lisfd,NULL,NULL);
                ERROR_CHECK(conn_fd,-1,"accept");
                add_epoll_fd(epfd,fd);
                add_epoll_fd(epfd,STDIN_FILENO);
            }else if(fd==STDIN_FILENO){
                char buff[100]={0};
                read(STDIN_FILENO,buff,sizeof(buff));
                int count = send(conn_fd,buff,sizeof(buff),0);
                printf("send to client num :%d\n",count);
            }else{
                char buff[100]={0};
                int cnt = recv(fd,buff,sizeof(buff),0);
                if(cnt == 0){
                    printf("client closed.\n");
                    del_epoll_fd(epfd,fd);
                    del_epoll_fd(epfd,STDIN_FILENO);
                    add_epoll_fd(epfd,lisfd);
                    close(conn_fd);
                    break;
                }
                printf("recv from client : %s\n",buff);
            }
        }
    }

    close(lisfd);
    close(conn_fd);
    return 0;
}

