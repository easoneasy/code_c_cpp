#ifndef __EPOLL_H__
#define __EPOLL_H__
#include<my_header.h>
typedef struct node_s{
    int fd;
    struct node_s *next;
}node_t;

typedef struct queue_s{
    node_t *head;
    node_t *tail;
    int size;
}queue_t;

int addqueue(queue_t *node,int fd);

int delqueue(queue_t *node);

#endif
