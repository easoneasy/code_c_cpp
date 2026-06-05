#include <my_header.h>

int main(int argc,char *argv[])
{
    for(int i=0;i<3;i++){
        fork();

        printf("a----%d",getpid());
    }
    fflush(stdout);

    return 0;
}

