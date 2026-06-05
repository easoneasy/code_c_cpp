#ifndef __PTHREAD_POOL_H__
#define __PTHREAD_POOL_H__
#include <my_header.h>
#include "queue.h"
typedef struct  thread_pool{
    int thread_num;
    //定义存放线程id的数组，不能写成pthread_t pthread_arr[thread_num];
    //因为thread_num是变量，结构体中不能定义长度不确定的数组
    //结构体的大小要在编译时就应该确定，而不是不确定的
    //可以定义指针，使用的时候再动态申请数组。
    pthread_t *pthread_arr;
    //将队列写入这个模块的原因是：
    //队列是线程池的私有财产，
    //如果有多个线程池还定义全局变量队列时会造成维护麻烦的问题
    //只有线程池内的线程可以使用这个队列
    //
    //队列的全部数据直接嵌入结构体内部，作为结构体的一块连续内存
    //写入的queue是这个队列结构体本身，而不是包括很多结点的一整个队列
    //队列还会增删结点，但是结点不算入此结构体内
    //queue_t *queue 这样写需要为整个队列动态申请空间
    queue_t queue;
    pthread_mutex_t lock;
    pthread_cond_t cond;
    int flag;
}threadpool_t;

//初始化线程池函数
void init_pthread_pool(int num,threadpool_t *thread_pool);

#endif
