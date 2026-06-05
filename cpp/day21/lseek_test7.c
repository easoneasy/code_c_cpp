#include <my_header.h>
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    
    int src_fp=open(argv[1],O_RDONLY);
    ERROR_CHECK(src_fp,-1,"src open failed.\n");
    int dest_fp=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0666);
    ERROR_CHECK(dest_fp,-1,"dest open failed.\n");
    
    off_t file_size = lseek(src_fp,0,SEEK_END);
    lseek(src_fp,0,SEEK_SET);
    char*  buff = (char *)malloc(file_size+1);
    ssize_t count=0;
    
    while((count=read(src_fp,buff,sizeof(buff)))!=0){
        write(dest_fp,buff,count);
    }

    return 0;
}

