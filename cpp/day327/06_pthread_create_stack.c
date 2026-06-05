#include <my_header.h>
void *thread_func(void *arg){
    printf("child thread.\n");
    int *p=(int *)arg;
    *p=30;
    return NULL;
}
int main(int argc,char *argv[]){
    int num =10;
    pthread_t thread_id;
    int ret = pthread_create(&thread_id,NULL,thread_func,(void *)&num);
    THREAD_ERROR_CHECK(ret,"thread create failed.\n");

    printf("mian thread.\n");
    sleep(5);
    printf("num = %d\n",num);
    return 0;
}

