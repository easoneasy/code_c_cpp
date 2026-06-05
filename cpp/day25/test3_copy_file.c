#include <my_header.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int srcp = open(argv[1],O_RDONLY);
    ERROR_CHECK(srcp,-1,"open file failed.\n");
    int destp = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0666);
    ERROR_CHECK(destp,-1,"open file failed.\n");

    char buff[4096]={0};
    ssize_t count =0 ;
    while((count=read(srcp,buff,sizeof(buff)))!=0){
        write(destp,buff,count);

    }

    close(srcp);
    close(destp);


    return 0;
}

