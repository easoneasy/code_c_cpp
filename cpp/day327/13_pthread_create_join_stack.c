#include <my_header.h>
void *thread_func(void *arg){
    printf("child thread.\n");
    /* int *num = (int *)malloc(10); */
    /* *num = 50; */
    static  int num =100;
    return (void *)&num;
    //局部变量的地址，函数结束之后局部变量销毁
}

int main(int argc,char *argv[]){
    pthread_t thread_id;
    int ret = pthread_create(&thread_id,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(ret,"thread create failed.\n");

    void *retval;
    ret = pthread_join(thread_id,&retval);
    THREAD_ERROR_CHECK(ret,"thread join failed.\n");
    printf("thread join over.\n");

    int *ptmp = (int *)retval;
    printf("ptmp = %d\n",*ptmp);


    return 0;
}

