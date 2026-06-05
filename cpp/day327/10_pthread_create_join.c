#include <my_header.h>
void *thread_func(void *arg){

    int *p=(int *)malloc(4);
    *p=30;
    return (void *)p;
}
int main(int argc,char *argv[]){
    pthread_t pthread_id;
    int ret = pthread_create(&pthread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"thread create faild.\n");
    void *tmp;
    pthread_join(pthread_id,&tmp);
    THREAD_ERROR_CHECK(ret,"thread join.\n");
    printf("thread join over.\n");
    int *p=(int *)tmp;
    printf("thread join p = %d\n",*p);
    return 0;
}

