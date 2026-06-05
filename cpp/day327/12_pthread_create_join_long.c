#include <my_header.h>
void *thread_func(void *arg){
    printf("child thread.\n");
    long p = 100;
    return (void *)p;
}
int main(int argc,char *argv[]){
    pthread_t pthread_id;
    int ret = pthread_create(&pthread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"thrad create faild.\n");

    void *retval;
    ret = pthread_join(pthread_id,&retval);
    THREAD_ERROR_CHECK(ret,"thread join failed.\n");
    printf("pthread join over.\n");

    long ptmp = (long) retval;
    printf("ptmp = %ld\n",ptmp);


    return 0;
}

