#include <my_header.h>
int global_num=0;
pthread_mutex_t lock;
void *thread_func(void *arg){
    printf("child thread begin.\n");
    for(int i=0;i<1000000;i++){
        int ret = pthread_mutex_lock(&lock);
        THREAD_ERROR_CHECK(ret,"thread lock");
        global_num++;
        ret = pthread_mutex_unlock(&lock);
        THREAD_ERROR_CHECK(ret,"pthread unlcok");

    }
    printf("child thread over.\n");
    pthread_exit((void *)NULL);
}
int main(int argc,char *argv[]){
    pthread_t pthread_id;
    int ret = pthread_create(&pthread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"thread create failed.\n");

    ret = pthread_mutex_init(&lock,NULL);
    THREAD_ERROR_CHECK(ret,"thread mutex");

    for(int i=0;i<1000000;i++){
        ret = pthread_mutex_lock(&lock);
        THREAD_ERROR_CHECK(ret,"pthread mutex lock");
        global_num++;
        ret = pthread_mutex_unlock(&lock);
        THREAD_ERROR_CHECK(ret,"pthread mutex unlock");
    }
    ret = pthread_join(pthread_id,NULL);
    THREAD_ERROR_CHECK(ret,"pthread join");
    printf("global num = %d\n",global_num);

    ret = pthread_mutex_destroy(&lock);
    THREAD_ERROR_CHECK(ret,"pthread destroy");

    return 0;
}

