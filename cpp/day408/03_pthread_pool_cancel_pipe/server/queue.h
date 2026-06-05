#ifndef __QUEUE_H__
#define __QUEUE_H__
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

int insert_queue(int fd,queue_t *queue);

int delete_quque(queue_t *queue);

#endif
