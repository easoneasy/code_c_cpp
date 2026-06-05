#include <my_header.h>

void *thread_func(void *arg)
{
    printf("I am son\n");

    long tmp = (long)arg;
    tmp = 30;
    printf("tmp: %ld\n", tmp);

    return NULL;
}

int main(int argc, char *argv[])
{
    long num = 10;

    pthread_t thread_id;
    int ret = pthread_create(&thread_id, NULL, thread_func, (void *)num);
    THREAD_ERROR_CHECK(ret, "pthread_create");

    printf("I am main\n");
    printf("***num : %ld\n", num);

    sleep(5);

    printf("num : %ld\n", num);

    return 0;
}


