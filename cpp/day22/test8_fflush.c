#include <my_header.h>

int main(int argc,char *argv[])
{
    FILE *fp = fopen("222.txt","w");
    ERROR_CHECK(fp,NULL,"fp open failed.\n");
    fputs("hello",fp);
    fflush(fp);
    write(3,"world",5);
    fclose(fp);


    return 0;
}

