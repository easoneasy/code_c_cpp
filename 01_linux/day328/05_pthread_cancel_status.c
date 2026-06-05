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

    ret = pthread_cancel(pthread_id);
    THREAD_ERROR_CHECK(ret,"thread cancel failed.\n");
    printf("ret = %d\n",ret);

    void *retval;
    ret=pthread_join(pthread_id,&retval);
    THREAD_ERROR_CHECK(ret,"thread join failed.\n");
    printf("main thread over.\n");

    if(retval==PTHREAD_CANCELED){
        printf("retval:%ld\n",(long)retval);
    }


    return 0;
}

