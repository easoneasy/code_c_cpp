#include <my_header.h>
void func(){
    printf("func\n");
    return ;
}
void *thread_func(void *arg){
    printf("child thread.\n");
    func();
    printf("child thread func over.\n");
    return NULL;
}
int main(int argc,char *argv[]){
    pthread_t thread_id;
    int ret = pthread_create(&thread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"thread create failed.\n");

    printf("main thread.\n");
    ret = pthread_join(thread_id,NULL);
    THREAD_ERROR_CHECK(ret,"thread join failed.\n");
    printf("main thread over.\n");


    return 0;
}

