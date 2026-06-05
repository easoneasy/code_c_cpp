#include <my_header.h>
pthread_mutex_t lock1,lock2;
void *thread_func(void *arg){
    printf("child thread begin.\n");
    int ret=0;
    while(1){
        ret = pthread_mutex_lock(&lock2);
        THREAD_ERROR_CHECK(ret,"child lock2");
        printf("child thread sleep begin.\n");
        sleep(1);
        printf("child thread sleep over.\n");
        ret = pthread_mutex_trylock(&lock1);
        THREAD_ERROR_CHECK(ret,"child lock1");
        if(ret!=0){
            pthread_mutex_unlock(&lock2);
            printf("child thread unlock2.\n");
            sleep(1);
            continue;
        }

        ret = pthread_mutex_unlock(&lock1);
        THREAD_ERROR_CHECK(ret,"child unlock1");
        ret = pthread_mutex_unlock(&lock2);
        THREAD_ERROR_CHECK(ret,"child unlock2");
        printf("child thread over.\n");
        break;
    }
    pthread_exit((void *)NULL);
}

int main(int argc,char *argv[]){
    int ret=0;
    pthread_t pthread_id;
    ret = pthread_create(&pthread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"pthread create");

    ret = pthread_mutex_init(&lock1,NULL);
    THREAD_ERROR_CHECK(ret,"main lock1 init");
    ret = pthread_mutex_init(&lock2,NULL);
    THREAD_ERROR_CHECK(ret,"main lock2 init");

    ret = pthread_mutex_lock(&lock1);
    THREAD_ERROR_CHECK(ret,"mian lock1 lock");
    printf("main thread sleep begin.\n");
    sleep(1);
    printf("main thread sleep over.\n");
    ret = pthread_mutex_lock(&lock2);
    THREAD_ERROR_CHECK(ret,"main lock2 lock");

    printf("mian thread get locks over.\n");

    ret=pthread_mutex_unlock(&lock1);
    THREAD_ERROR_CHECK(ret,"main unlock1");
    ret=pthread_mutex_unlock(&lock2);
    THREAD_ERROR_CHECK(ret,"main unlock2");
    printf("main unlocks\n");

    ret = pthread_join(pthread_id,NULL);
    THREAD_ERROR_CHECK(ret,"main thread join");

    ret = pthread_mutex_destroy(&lock1);
    THREAD_ERROR_CHECK(ret,"mian destroy lock1");
    ret = pthread_mutex_destroy(&lock2);
    THREAD_ERROR_CHECK(ret,"mian destroy lock2");

    return 0;
}

