#include <my_header.h>
#include"work.h"

void *work_thread_func(void *arg){
    
    printf("work \n");
    threadpool_t *pthread_pool =(threadpool_t *)arg;
    while(1){
        //加锁
        pthread_mutex_lock(&pthread_pool->lock);
        //如果队列为空就睡
        //之前队列判空的时候返回一个返回值
        printf("work pthread_cond_wait\n");
        while(pthread_pool->queue.size==0){
            pthread_cond_wait(&pthread_pool->cond,&pthread_pool->lock);
            
        }
        //删除结点
        printf("work delete_queue\n");
        int del_fd=delete_queue(&pthread_pool->queue);
        printf("%d fd was deleted.\n",del_fd);
        //解锁
        pthread_mutex_unlock(&pthread_pool->lock);
        
        send_file(del_fd);
    }
}

