#include <my_header.h>

int main(int argc,char *argv[])
{
    FILE *fp = fopen("11.txt","w");
    ERROR_CHECK(fp,NULL,"fopen failed.\n");
    fputc('a',fp);
    fputc('b',fp);
    /* close(3); */
    fclose(fp);

    return 0;
}

