#include <my_header.h>
#include"pthread_pool.h"
#include"work.h"

void init_thread_pool(pthread_pool *pool,int num){
   
    pool->pthread_num=num;
    
    pool->pthread_id=(pthread_t *)calloc(num,sizeof(pthread_t));

    pthread_mutex_init(&pool->lock,NULL);
    pthread_cond_init(&pool->cond,NULL);

    memset(&pool->queue,0,sizeof(queue_t));

    for(int i=0;i<num;i++){
        pthread_create(&pool->pthread_id[i],NULL,pthread_work_func,(void *)pool);
    }
}
