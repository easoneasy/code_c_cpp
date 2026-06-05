#include <my_header.h>
void *thread_func(void *arg){
    while(1){
        sleep(1);
    }
    pthread_exit(NULL);
}

int main(int argc,char *argv[]){
    pthread_t pthread_id;
    int ret = pthread_create(&pthread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"thread create failed.\n");

    sleep(1);
    printf("main.\n");
    ret = pthread_cancel(pthread_id);
    THREAD_ERROR_CHECK(ret,"thread cancel failed.\n");
    printf("ret : %d\n",ret);

    ret = pthread_join(pthread_id,NULL);
    THREAD_ERROR_CHECK(ret,"thread join failed.\n");
    printf("main over.\n");


    return 0;
}

