#include <my_header.h>

int main(int argc, char *argv[]){
    printf("open read before.\n");
    int read_p = open("1.pipe", O_RDONLY);
    printf("open read after.\n");
    ERROR_CHECK(read_p, -1, "open read failed");

    char buf[4096] = {0};
    for(int i=0; i<10; i++){
        printf("read begin.\n");
        ssize_t ret = read(read_p, buf, sizeof(buf));
        printf("read end.\n");
        printf("round----------%d---------total_num:%ld\n",i,ret);
    }

    printf("sleep begin.\n");
    sleep(20);
    printf("sleep end.\n");
    printf("test7_read over, byebye!\n");
    close(read_p);

    return 0;
}

