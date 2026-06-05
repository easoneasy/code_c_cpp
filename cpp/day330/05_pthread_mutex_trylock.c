#include <my_header.h>
pthread_mutex_t lock;
void *thread_func(void *arg){
    printf("child thread begin.\n");
    int ret=0;
    while(1){
        ret=pthread_mutex_lock(&lock);
        THREAD_ERROR_CHECK(ret,"child lock");
        if(ret!=0){
            break;
        }
    }
    printf("child sleep.\n");
    /* sleep(1); */
    printf("child sleep over.\n");
    ret=pthread_mutex_unlock(&lock);
    THREAD_ERROR_CHECK(ret,"child thread unlock");

    pthread_exit((void *)NULL);
}
int main(int argc,char *argv[]){
    pthread_t pthread_id;
    int ret = pthread_create(&pthread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"thread create");
    
    ret=pthread_mutex_init(&lock,NULL);
    THREAD_ERROR_CHECK(ret,"main thread init");

    ret = pthread_mutex_lock(&lock);
    THREAD_ERROR_CHECK(ret,"main thread lock");

    printf("main sleep begin\n");
    sleep(100);
    printf("mian sleep over.\n");

    ret=pthread_mutex_unlock(&lock);
    THREAD_ERROR_CHECK(ret,"main thread unlock");

    ret=pthread_join(pthread_id,NULL);
    THREAD_ERROR_CHECK(ret,"main thread join");

    ret=pthread_mutex_destroy(&lock);
    THREAD_ERROR_CHECK(ret,"lock destroy");


    return 0;
}

