#include <my_header.h>
pthread_mutex_t lock;
pthread_cond_t cond;
void *thread_func(void *arg){
    sleep(1);
    printf("child  thread begin.\n");
    pthread_mutex_lock(&lock);
    printf("child  thread lock.\n");
    sleep(3);
    pthread_cond_signal(&cond);
    printf("child thread signal.\n");
    pthread_mutex_unlock(&lock);
    printf("child  thread over.\n");
    pthread_exit((void *)NULL);
}

int main(int argc,char *argv[]){
    int ret=0;
    pthread_t pthread_id;
    ret = pthread_create(&pthread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"thread B create");

    pthread_mutex_init(&lock,NULL);

    pthread_cond_init(&cond,NULL);

    pthread_mutex_lock(&lock);
    
    printf("cond and sleep begin.\n");
    printf("begin wait\n");
    struct timeval now;
    struct timespec tm;
    gettimeofday(&now,NULL);
    tm.tv_sec=now.tv_sec+100;
    tm.tv_nsec=0;
    ret = pthread_cond_timedwait(&cond,&lock,&tm);
    printf("ret = %d\n",ret);
    printf("cond over.\n");
    
    pthread_mutex_unlock(&lock);
    printf("main wait child.\n");
    pthread_join(pthread_id,NULL);

    printf("main wait child over.\n");
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}

