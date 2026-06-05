#include <my_header.h>
void *thread_func(void * arg){
    printf("child .\n");
    return NULL;
}
int main(int argc,char *argv[]){
    
    pthread_t thread_id;
    pthread_create(&thread_id,NULL,thread_func,NULL);

    printf(" main .\n");
    return 0;
}

