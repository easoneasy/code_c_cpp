#include <my_header.h>

int main(int argc, char *argv[]){
    printf("open write begin.\n");
    int write_p = open("1.pipe", O_WRONLY);
    printf("open write end.\n");
    ERROR_CHECK(write_p, -1, "open write failed");
    char buf[4096] = {0};
    for(int i=0; i<1000; i++){
        printf("write begin\n");
        ssize_t ret=write(write_p, buf, sizeof(buf));
        printf("write end\n");
        printf("round-------%d-------total_num:%ld.\n",i,ret);
    }

    printf("write loop end.\n");

    close(write_p);

    return 0;
}


