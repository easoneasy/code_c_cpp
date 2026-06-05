#include <my_header.h>
pthread_mutex_t lock;
pthread_cond_t cond;
void *thread_funcA(void *arg){
    sleep(1);
    printf("child A thread begin.\n");
    pthread_mutex_lock(&lock);
    printf("child A thread lock.\n");

    pthread_cond_wait(&cond,&lock);
    printf("child A wait over.\n");
    pthread_mutex_unlock(&lock);
    printf("child A thread over.\n");
    pthread_exit((void *)NULL);
}
void *thread_funcB(void *arg){
    sleep(1);
    printf("child B thread begin.\n");
    pthread_mutex_lock(&lock);
    printf("child B thread lock.\n");

    pthread_cond_wait(&cond,&lock);
    printf("child B wait over.\n");
    pthread_mutex_unlock(&lock);
    printf("child B thread over.\n");
    pthread_exit((void *)NULL);
}

int main(int argc,char *argv[]){
    int ret=0;
    pthread_t pthread_idA,pthread_idB;
    ret = pthread_create(&pthread_idA,NULL,thread_funcA,NULL);
    THREAD_ERROR_CHECK(ret,"thread B create");
    ret = pthread_create(&pthread_idB,NULL,thread_funcB,NULL);
    THREAD_ERROR_CHECK(ret,"thread B create");

    pthread_mutex_init(&lock,NULL);

    pthread_cond_init(&cond,NULL);

    /* pthread_mutex_lock(&lock); */
    
    printf("cond and sleep begin.\n");
    sleep(5);
    pthread_cond_broadcast(&cond);
    printf("cond over.\n");
    
    /* pthread_mutex_unlock(&lock); */
    printf("main wait child.\n");
    pthread_join(pthread_idA,NULL);
    pthread_join(pthread_idB,NULL);
    printf("main wait child over.\n");
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}

