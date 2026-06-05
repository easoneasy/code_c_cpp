#include <my_header.h>
pthread_mutex_t lock;
int global=0;
void *func(void *arg){
    printf("child thread.\n");
    for(int i=0;i<2000000;i++){
        pthread_mutex_lock(&lock);
        global++;
        pthread_mutex_unlock(&lock);
    }

    pthread_exit((void *)NULL);
}
int main(int argc,char *argv[]){
    pthread_t id;
    pthread_create(&id,NULL,func,NULL);

    pthread_mutex_init(&lock,NULL);
    struct timeval begin, end;
    gettimeofday(&begin,NULL);

    printf("main thread.\n");

    for(int i=0;i<2000000;i++){
        pthread_mutex_lock(&lock);
        global++;
        pthread_mutex_unlock(&lock);
    }

    pthread_join(id,NULL);
    printf("global = %d\n",global);
    pthread_mutex_destroy(&lock);
    gettimeofday(&end,NULL);
    printf("time = %ld\n",(end.tv_sec-begin.tv_sec)*1000000+(end.tv_usec-begin.tv_usec));


    return 0;
}

