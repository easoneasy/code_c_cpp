#include "queue.h"



int addqueue(queue_t *queue,int fd){
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
    return 0;
}

int delqueue(queue_t *queue){
    if(queue->size==0){
        return -1;
    }
    node_t *p=queue->head;
    queue->head=p->next;
    if(queue->size==1){
        queue->tail=NULL;
    }
    free(p);
    queue->size--;
    return 0;
}

