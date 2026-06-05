#include <my_header.h>

int main(int argc,char *argv[]){
    char *ptmp = "192.168.254.128";

    struct in_addr addr;
    inet_aton(ptmp,&addr);

    printf("%d\n",addr.s_addr);

    char *pc = inet_ntoa(addr);
    printf("%s\n",pc);


    return 0;
}

