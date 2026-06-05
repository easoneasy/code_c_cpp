#include <my_header.h>
void *thread_func(void *arg){
    printf("child thread.\n");
    int *p=(int *)malloc(10);
    *p=50;
    return (void *)p;
}
int main(int argc,char *argv[]){
    pthread_t pthread_id;
    int ret = pthread_create(&pthread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"thread create failed.\n");
    
    void **ptmp=(void **)malloc(10);
    ret = pthread_join(pthread_id,ptmp);
    THREAD_ERROR_CHECK(ret,"thread join failed.\n");
    printf("thread join over.\n");

    int retval = *(int *)*ptmp;
    printf("retval=%d\n",retval);
    
    free(*ptmp);
    *ptmp=NULL;
    free(ptmp);
    ptmp=NULL;
    return 0;
}

