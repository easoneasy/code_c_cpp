#include <my_header.h>
#include"epoll.h"

//将fd放在红黑树上监听
void add_epoll_ctl(int epfd,int fd){
    struct epoll_event evt;
    evt.events=EPOLLIN;
    evt.data.fd=fd;

    epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&evt);
}

//将fd从红黑树上取消监听
void del_epoll_ctl(int epfd,int fd){
    struct epoll_event evt;
    evt.events=EPOLLOUT;
    evt.data.fd=fd;

    epoll_ctl(epfd,EPOLL_CTL_DEL,fd,&evt);

}
