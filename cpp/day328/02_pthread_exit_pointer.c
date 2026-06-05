#include <my_header.h>
void func(){
    printf("func \n");
    static int num = 100;
    pthread_exit((void *)&num);

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

    int *p=(int *)num;
    printf("pthread exit retval=%d\n",*p);
    num = NULL;
    return 0;
}

