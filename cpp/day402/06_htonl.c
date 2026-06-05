#include <my_header.h>

int main(int argc,char *argv[]){
    int num = 0x34353637;
    char *p = (char *)&num;
    printf("%c\n",*p);
    
    int a = htonl(num);
    char *pa = (char *)&a;
    printf("%c\n",*pa);

    return 0;
}

