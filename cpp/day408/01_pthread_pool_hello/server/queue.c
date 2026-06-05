#include"queue.h"
#include<my_header.h>
//入队函数
void insert_queue(queue_t *queue,int fd){
    //创建新结点，初始化
    printf("quque-------insert_queue\n");
    node_t *new_node=(node_t *)calloc(1,sizeof(node_t));
    new_node->fd=fd;
    new_node->next=NULL;
    //空队列就让头尾指针都指向这个新结点
    if(queue->size==0){
        queue->head=new_node;
        queue->tail=new_node;
    }else{  
        //非空结点就尾插
        queue->tail->next=new_node;
        queue->tail=new_node;
    }
    queue->size++;
    printf("queue--------insert_queue over------\n");
} 

//出队函数
int delete_queue(queue_t *queue){
    
    printf("quque-------del_queue\n");
    //空队列，就等待主线程写入文件描述符之后
    if(queue->size==0){
        return -1;
    }

    //非空队列就头删
    node_t *p = queue->head;
    queue->head=p->next;
    //判断是否为唯一结点，维护尾指针
    if(queue->size==1){
    queue->tail=NULL;
     
    }
    int del_fd=p->fd;
    free(p);
    queue->size--;
    printf("queue--------del_queue over------\n");
    return del_fd;
}
