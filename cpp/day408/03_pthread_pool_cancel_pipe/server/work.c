#include <my_header.h>
#include"work.h"

void clean_func(void *p){
    pthread_mutex_t *lock =(pthread_mutex_t *)p;
    pthread_mutex_unlock(lock);
    printf("clean_func unlock\n");
}

//线程入口函数，子线程从队列中拿文件描述符
void *pthread_work_func(void *arg){
    pthread_pool *pool=(pthread_pool *)arg;
    
    while(1){
        int del_fd=0;
        //从队列中拿文件描述符
        //加锁
        pthread_mutex_lock(&pool->lock);
        pthread_cleanup_push(clean_func,(void *)&pool->lock);
        //读空阻塞
        while(pool->queue.size==0){
            pthread_cond_wait(&pool->cond,&pool->lock);
        }
        //拿文件描述符
        del_fd = delete_quque(&pool->queue);
        //解锁
        /* pthread_mutex_unlock(&pool->lock); */
        pthread_cleanup_pop(1);

        printf("work-------send_file begin.\n");
        //发送数据
        send_file(del_fd);
    }
}
