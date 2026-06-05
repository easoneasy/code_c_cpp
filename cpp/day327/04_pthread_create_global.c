#include <my_header.h>

int global_num = 0;
void *thread_func(void *arg){
    printf("child thread.\n");
    for(int i=0;i<1000000;i++){
        ++global_num;
    }
    printf("child thread global_num = %d\n",global_num);
    
    return NULL;
}


int main(int argc,char *argv[]){
    pthread_t pthread_id;
    int ret = pthread_create(&pthread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"thread create faild.\n");

    for(int i=0;i<1000000;i++){
        ++global_num;
    }

    printf("main thread.\n");
    
    sleep(3);
    printf("global_num = %d\n",global_num);



    return 0;
}

