#include <my_header.h>
void *thread_func(void *arg){
    printf("child thread.\n");
    char *p = (char *)arg;
    strcpy(p,"hello");
    return NULL;
}
int main(int argc,char *argv[]){
    char *ptmp=(char *)malloc(10*sizeof(char));

    pthread_t pthread_id;
    int ret = pthread_create(&pthread_id,NULL,thread_func,(void *)ptmp);
    THREAD_ERROR_CHECK(ret,"thread create failed.\n");

    printf("main thread.\n");

    sleep(3);

    printf("ptmp : %s\n",ptmp);

    free(ptmp);
    ptmp=NULL;


    return 0;
}

