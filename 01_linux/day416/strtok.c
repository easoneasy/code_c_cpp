#include <my_header.h>

int main(int argc,char*argv[])
{
    char str[] = "cd    abc/def/dir";
    // mkdir x
    // rm   x

    char *p = strtok(str,  " ");
    printf( "p=%s  \n",   p);
    //p = strtok(NULL,  " /");
    p = strtok(NULL,  "/");
    printf( "p=%s  \n",   p);
    p = strtok(NULL,  "/");
    printf( "p=%s  \n",   p);
    p = strtok(NULL,  "/");
    printf( "p=%s  \n",   p);

    return 0;
}
