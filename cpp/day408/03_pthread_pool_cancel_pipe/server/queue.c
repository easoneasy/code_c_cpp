#include <my_header.h>
#include"queue.h"
//向队列中插入文件描述符
int insert_queue(int fd,queue_t *queue){
    printf("insert_queue\n");
    node_t *new_node =(node_t *)calloc(1,sizeof(node_t));
    new_node->fd=fd;
    if(queue->size==0){
        queue->head=new_node;
        queue->tail=new_node;
    }else{
        queue->tail->next=new_node;
        queue->tail=new_node;
    }
    
    queue->size++;
    printf("insert_queue over.\n");
    return queue->size;

} 

int delete_quque(queue_t *queue){
    if(queue->size==0){
        return -1;
    }

    node_t *p=queue->head;
    queue->head=p->next;
    if(queue->size==1){
       queue->tail=NULL; 
    }
    queue->size--;
    int del_fd = p->fd;
    free(p);
    return del_fd;

}
