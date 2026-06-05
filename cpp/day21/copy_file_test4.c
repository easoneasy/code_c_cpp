#include <my_header.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);

    int src_fd = open(argv[1],O_RDONLY);
    ERROR_CHECK(src_fd,-1,"src open failed.\n");

    int dest_fd = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0764);
    ERROR_CHECK(dest_fd,-1,"dest open failed.\n");

    char buff[100]={0};
    ssize_t count =0;
    while((count = read(src_fd,buff,sizeof(buff)))!=0){
        write(dest_fd,buff,count);

    }
    close(src_fd);
    close(dest_fd);


    return 0;
}

