#include <my_header.h>
void *pthread_func(void *arg){
    printf("---------child thread id = %ld\n",pthread_self());
    printf("---------child thread.\n");
    return NULL;
}
int main(int argc,char *argv[]){
    pthread_t pthread_id;
    int ret = pthread_create(&pthread_id,NULL,pthread_func,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create failed.\n");

    printf("child thread id = %ld\n",pthread_id);
    printf("father thread id = %ld\n",pthread_self());

    /* sleep(1); */
    while(1);


    return 0;
}

