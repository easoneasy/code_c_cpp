#include <my_header.h>
void free_func(void *p){
    printf("free func.\n");
    char *tmp=(char *)p;
    free(tmp);
    tmp=NULL;
}
void close_func(void *p){
    printf("close func.\n");
    int *fd = (int *)p;
    close(*fd);
}
void *thread_func(void *arg){
    printf("child thread.\n");
    char *p = (char *)malloc(10);
    strcpy(p,"hello");
    pthread_cleanup_push(free_func,p);
    
    int fd = open("1.txt",O_RDONLY);
    pthread_cleanup_push(close_func,(void *)&fd);

    sleep(3);
    printf("child thread.\n");
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    printf("child thread over.\n");
    pthread_exit(NULL);
}

int main(int argc,char *argv[]){
    pthread_t pthread_id;
    int ret = pthread_create(&pthread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"thread create failed.\n");

    sleep(1);
    ret = pthread_cancel(pthread_id);
    THREAD_ERROR_CHECK(ret,"thread cancel failed.\n");

    void *retval;
    ret = pthread_join(pthread_id,&retval);
    THREAD_ERROR_CHECK(ret,"thread join failed.\n");
    printf("retval = %ld\n",(long)retval);
    return 0;
}

