#include <my_header.h>
pthread_mutex_t lock1;
pthread_mutex_t lock2;
void *thread_func(void *arg){
    printf("child thread begin.\n");
    pthread_mutex_lock(&lock2);
    printf("child thread lock2.\n");
    sleep(1);
    int ret = pthread_mutex_trylock(&lock1);
    THREAD_ERROR_CHECK(ret,"child thread trylock.");
    printf("child thread lock1.\n");
    printf("child thread get lock over.\n");
    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
    printf("child thread lock over.\n");

    pthread_exit((void *)NULL);
}

int main(int argc,char *argv[]){
    pthread_mutex_init(&lock1,NULL);
    pthread_mutex_init(&lock2,NULL);

    pthread_t pthread_id;
    pthread_create(&pthread_id,NULL,thread_func,NULL);


    pthread_mutex_lock(&lock1);
    printf("mian thread get lock1.\n");
    sleep(1);
    pthread_mutex_lock(&lock2);
    printf("main thread get lock2.\n");

    printf("main thread lock over.\n");

    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
    printf("main thread unlock over.\n");

    pthread_join(pthread_id,NULL);

    int ret = pthread_mutex_destroy(&lock1);
    THREAD_ERROR_CHECK(ret,"main thread destroy lock1.");
    ret = pthread_mutex_destroy(&lock2);
    THREAD_ERROR_CHECK(ret,"main thread destroy lock2.");
    return 0;
}

