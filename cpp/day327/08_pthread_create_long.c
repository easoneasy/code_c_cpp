#include <my_header.h>
void *thread_func(void *arg){
    printf("child thread.\n");
    long p = (long) arg;
    p=30;
    printf("child num = %ld\n",p);
    return NULL;
}
int main(int argc,char *argv[]){
    long num = 10;
    pthread_t pthread_id;
    int ret = pthread_create(&pthread_id,NULL,thread_func,(void *)num);
    THREAD_ERROR_CHECK(ret,"therad create faild.\n");
    printf("main thread.\n");
    printf("main num = %ld\n",num);
    sleep(3);
    printf("num : %ld\n",num);


    return 0;
}

