#include <my_header.h>
pthread_mutex_t lock;
pthread_cond_t cond;
int flag=0;
void *func(void *arg){
    printf("son thread.\n");
    pthread_mutex_lock(&lock);
    if(flag==0){
        printf("b wait.\n");
        pthread_cond_wait(&cond,&lock);
        printf("B\n");
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }
    pthread_exit((void *)NULL);
}
int main(int argc,char *argv[]){
    pthread_t id;

    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&cond,NULL);
    pthread_create(&id,NULL,func,NULL);

    printf("main thread.\n");
    pthread_mutex_lock(&lock);
    if(flag==0){

        printf("A\n");
        pthread_cond_signal(&cond);
        printf("c wait.\n");
        pthread_cond_wait(&cond,&lock);
        printf("c wait over.\n");
        printf("C\n");
        pthread_mutex_unlock(&lock);

    }
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}

