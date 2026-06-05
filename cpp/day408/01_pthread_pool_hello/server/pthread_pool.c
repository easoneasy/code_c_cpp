#include <my_header.h>
#include"pthread_pool.h"
#include"work.h"
//初始化线程池
void init_pthread_pool(int num,threadpool_t *thread_pool){
    printf("init_pthread_pool\n");
    //将线程的数目赋值
    thread_pool->thread_num=num;
    //为线程数目动态申请空间，存放线程id
    thread_pool->pthread_arr=(pthread_t *)malloc(num*sizeof(pthread_t));

    //初始化锁
    pthread_mutex_init(&thread_pool->lock,NULL);
    //初始化条件变量
    pthread_cond_init(&thread_pool->cond,NULL);

    //初始化队列
    memset(&thread_pool->queue,0,sizeof(queue_t));

    //创建线程函数
    for(int i=0;i<num;i++){

        pthread_create(&thread_pool->pthread_arr[i],NULL,work_thread_func,(void *)thread_pool);
    }
    printf("init_pthread_pool  over----------\n");
}
