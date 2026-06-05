#ifndef __THREAD_POLL__
#define __THREAD_POLL__
#include"queue.h"
#include<my_header.h>

typedef struct thread_poll{
    int thread_num;
    pthread_t *thread_id_arr;
    queue_t queue;
    pthread_mutex_t lock;
    pthread_cond_t cond;
}thread_poll_t;

void init_thread_poll(thread_poll_t *pool,int num);

#endif
