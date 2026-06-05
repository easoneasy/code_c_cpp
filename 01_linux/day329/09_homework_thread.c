#include <my_header.h>
void *thread_func(void *arg){
    printf("child thread.\n");
    long ptmp =100;
    return (void *)ptmp;
}
int main(int argc,char *argv[]){
    pthread_t pthread_id[3];
    for(int i=0;i<3;i++){
        int ret = pthread_create(&pthread_id[i],NULL,thread_func,NULL);
        THREAD_ERROR_CHECK(ret,"pthread create failed.\n");
    }
    
    void *retval;
    for(int i=0;i<3;i++){
        printf("wait child thread.\n");
        pthread_join(pthread_id[i],&retval);
        printf("retval = %ld\n",(long)retval);
    }
    

    return 0;
}

