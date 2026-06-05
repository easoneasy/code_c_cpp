#ifndef __EPOLL_H__
#define __EPOLL_H__



void add_epoll_ctl(int epfd,int fd);

void del_epoll_ctl(int epfd,int fd);


#endif
