#include <my_header.h>

int main(int argc,char *argv[])
{
    printf("hello\n");
    
    fwrite("world\n",1,6,stdout);


    return 0;
}

