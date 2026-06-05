#include <my_header.h>

int main(int argc,char *argv[])
{   
    char buff[100]={0};
    char * ret1 = getcwd(buff,sizeof(buff));
    printf("buff = %s\n",buff);

    chdir("../day18");

    char * ret2 = getcwd(buff,sizeof(buff));
    printf("buff =%s\n",buff);

    return 0;
}

