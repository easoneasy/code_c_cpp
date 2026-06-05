#include <my_header.h>

int main(int argc,char *argv[])
{
    FILE *fp=fopen("1.txt","r");
    ERROR_CHECK(fp,NULL,"fp open failed.\n");
    
    int ret=chdir("../day18");
    printf("ret =%d\n",ret);

    FILE *fp2=fopen("111.txt","r");
    ERROR_CHECK(fp2,NULL,"open failed.\n");


    return 0;
}

