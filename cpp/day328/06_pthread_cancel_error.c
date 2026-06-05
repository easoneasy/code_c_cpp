#include <my_header.h>
void *thread_func(void *arg){
    char *p = (char *)malloc(10);
    strcpy(p,"hello");

    int fd = open("1.txt",O_RDONLY);
    sleep(3);
    printf("son thread.\n");
    free(p);
    close(fd);
    pthread_exit(NULL);
}

int main(int argc,char *argv[]){
    pthread_t pthread_id;
    int ret = pthread_create(&pthread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"pthread create failed.\n");

    ret = pthread_cancel(pthread_id);
    THREAD_ERROR_CHECK(ret,"pthread cancel failed.\n");
    void *retval;
    ret=pthread_join(pthread_id,&retval);
    THREAD_ERROR_CHECK(ret,"thread join failed.\n");

    printf("main thread over.\n");
    if(retval==PTHREAD_CANCELED){
        printf("retval = %ld\n",(long)retval);
    }

    return 0;
}

