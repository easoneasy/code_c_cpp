#include <my_header.h>
void func(){
    printf("func \n");
    long num =100;
    pthread_exit((void *)num);

}
void *thread_func(void *arg){
    printf("child thread.\n");
    func();
    printf("child thread over.\n");
    return NULL;
}
int main(int argc,char *argv[]){
    pthread_t pthread_id;
    int ret = pthread_create(&pthread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"thread create failed.\n");

    printf("main thread.\n");
    void *num;
    ret = pthread_join(pthread_id,&num);
    THREAD_ERROR_CHECK(ret,"pthread join failed.\n");

    /* int *p=(int *)num; */
    long p = (long)num;
    printf("pthread exit retval=%ld\n",p);

    return 0;
}

