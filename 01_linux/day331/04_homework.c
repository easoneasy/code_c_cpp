#include <my_header.h>
pthread_mutex_t lock;
pthread_cond_t cond;
int flag =0;
void *func(void *arg){
    pthread_mutex_lock(&lock);
    while(flag==0){
        pthread_cond_wait(&cond,&lock);
    }
    printf("B\n");
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);


    pthread_exit((void *)NULL);
}
int main(int argc,char *argv[]){
    pthread_t id;
    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&cond,NULL);
    pthread_create(&id,NULL,func,NULL);
    pthread_mutex_lock(&lock);
    printf("A\n");
    flag=1;
    pthread_cond_signal(&cond);
    pthread_cond_wait(&cond,&lock);
    printf("C\n");
    pthread_mutex_unlock(&lock);


    pthread_join(id,NULL);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);


    return 0;
}

