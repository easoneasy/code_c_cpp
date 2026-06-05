#include"epoll.h"
#include <my_header.h>

void add_epoll_ctl(int epfd,int fd){
    struct epoll_event evt;
    evt.events=EPOLLIN;
    evt.data.fd=fd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&evt);

}
    
void del_epoll_ctl(int epfd,int fd){
    struct epoll_event evt;
    evt.events=EPOLLOUT;
    evt.data.fd=fd;
    epoll_ctl(epfd,EPOLL_CTL_DEL,fd,&evt);
}

