#include <my_header.h>
void *thread_func(void *arg){
    printf("child thread.\n");
    int *p = (int *)arg;
    *p=30;
    return NULL;
}
void func(){
    int num =10;
    pthread_t pthread_id;
    int ret = pthread_create(&pthread_id,NULL,thread_func,(void *)&num);
    THREAD_ERROR_CHECK(ret,"pthread create failed.\n");
    sleep(2);
    printf("num = %d\n",num);
}
int main(int argc,char *argv[]){
    func();
    printf("main thread.\n");
    sleep(5);
    return 0;
}

