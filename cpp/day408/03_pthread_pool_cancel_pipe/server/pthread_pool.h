#ifndef __PTHREAD_POOL_H__
#define __PTHREAD_POOL_H__
#include "queue.h"

typedef struct thread_pool{
    int pthread_num;
    pthread_t *pthread_id;
    queue_t queue;
    pthread_mutex_t lock;
    pthread_cond_t cond;

}pthread_pool;

void init_thread_pool(pthread_pool *pool,int num);

#endif
