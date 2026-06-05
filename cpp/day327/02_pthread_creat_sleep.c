#include <my_header.h>
void *thread_func(void *arg){
    printf("child.\n");
    return NULL;
}
int main(int argc,char *argv[]){
    pthread_t pthread_id;
    pthread_create(&pthread_id,NULL,thread_func,NULL);
    
    printf("main.\n");
    sleep(1);

    return 0;
}

