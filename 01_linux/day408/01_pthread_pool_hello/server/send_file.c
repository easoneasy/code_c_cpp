#include <my_header.h>
#include"send_file.h"

void send_file(int fd){
    
    printf("send_file ------------\n");
    send(fd,"hello",5,0);

}
