#include <my_header.h>
pthread_mutex_t lock1,lock2;
void *thread_func(void *arg){
    printf("child thread.\n");
    pthread_mutex_lock(&lock2);
    printf("child thread lock2 over.\n");
    pthread_mutex_lock(&lock1);
    printf("child thread lock1 over.\n");
    printf("child get locks over.\n");
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);

    pthread_exit((void *)NULL);
}
int main(int argc,char *argv[]){
    pthread_t pthread_id;
    pthread_create(&pthread_id,NULL,thread_func,NULL);

    pthread_mutex_init(&lock1,NULL);
    pthread_mutex_init(&lock2,NULL);

    pthread_mutex_lock(&lock1);
    printf("lock1 over.\n");
    pthread_mutex_lock(&lock2);
    printf("lock2 over.\n");

    printf("main thread lock1 and lock2\n");

    pthread_mutex_unlock(&lock1);
    printf("lock1 unlock\n");
    pthread_mutex_unlock(&lock2);
    printf("lock2 unlock\n");


    pthread_join(pthread_id,NULL);

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);
    return 0;
}

