#include <my_header.h>
void *thread_func(void *arg){
    printf("child thread.\n");
    while(1);
    return NULL;
}
int main(int argc,char *argv[]){
    pthread_t pthread_id;
    int ret = pthread_create(&pthread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"thread create faild.\n");
    printf("main thread.\n");
    pthread_join(pthread_id,NULL);
    printf("main thread over.\n");


    return 0;
}

