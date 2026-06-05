#include <my_header.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int num1;
    int num2;
    sscanf(argv[1],"%d",&num1);
    sscanf(argv[2],"%d",&num2);
    printf("%d + %d = %d\n",num1,num2,num1+num2);


    return 0;
}

