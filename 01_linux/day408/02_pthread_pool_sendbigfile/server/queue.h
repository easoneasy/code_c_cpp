#ifndef __QUEUE_H__
#define __QUEUE_H__

//定义结点结构体
typedef struct nodes{
    int fd;
    struct nodes *next;
}node_t;

//定义队列结构体
typedef  struct queue{
    node_t *head;
    node_t *tail;
    int size;
}queue_t;


//入队函数
void insert_queue(queue_t *queue,int fd);


//出队函数
int delete_queue(queue_t *queue);


#endif
