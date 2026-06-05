#include <my_header.h>

// 两个线程对同一个共享变量分别加一百万次: 使用锁
#define TIMES 1000000

int global = 0;

void * func(void *arg)
{
    pthread_mutex_t *pmLock = (pthread_mutex_t *)arg; // 接收主线程传参, 获得锁
    printf("child thread is runing \n");
    for(int i = 0; i<TIMES; i++)
    {
        pthread_mutex_lock(pmLock); // 加锁
        global++;
        pthread_mutex_unlock(pmLock); // 解锁
    }
    printf("child thread stop \n");
    return NULL;
}
int main(int argc,char* argv[])
{
    pthread_mutex_t mLock; // 定义锁
    pthread_mutex_init(&mLock, NULL);// 对锁初始化

    pthread_t pid;
    pthread_create(&pid,NULL,func, &mLock); // 把锁传给子线程
    
    printf("main thread is runing \n");
    for(int i = 0; i<TIMES; i++)
    {
        pthread_mutex_lock(&mLock); // 加锁
        global++;
        pthread_mutex_unlock(&mLock); // 解锁 
    }
    
    printf("main thread stop \n");
    
    pthread_join(pid, NULL);
    printf("all over, global = %d \n", global);
    pthread_mutex_destroy(&mLock); // 销毁锁

    return 0;
}
