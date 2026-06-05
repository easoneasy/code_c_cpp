#include <my_header.h>

int main(int argc,char *argv[])
{
   ARGS_CHECK(argc,2);
   int fd = open(argv[1],O_WRONLY | O_CREAT | O_TRUNC,0777);
   ERROR_CHECK(fd,-1,"fd open failed.\n");

   char buff[]="hello world";
   ssize_t ret = write(fd,buff,15);
   ERROR_CHECK(ret,-1,"write failed.\n");
   printf("%ld\n",ret);
   close(fd);    

    return 0;
}

