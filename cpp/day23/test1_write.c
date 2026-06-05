#include <my_header.h>

int main(int argc,char *argv[])
{
    int write_p = open("1.pipe",O_WRONLY);
    ERROR_CHECK(write_p,-1,"write open failed.\n");
    printf("write begin.\n");
    char buff[100]={"hello this is userb.how are you today?"};
    ssize_t ret = write(write_p,buff,sizeof(buff));
    printf("write over.\n");
    printf("ret = %ld\n",ret);

    close(write_p);

    return 0;
}

