#include <my_header.h>

int main(int argc,char *argv[]){
    char *ip = "192.168.254.128";
    char *port = "12345";

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    ERROR_CHECK(fd, -1, "socket");

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
    addr.sin_addr.s_addr = inet_addr(ip);

    sendto(fd, "hello", 5, 0, (struct sockaddr *)&addr, sizeof(addr));

    char buff[1024] = {0};
    socklen_t len = sizeof(addr);   
    recvfrom(fd, buff, 1024, 0, (struct sockaddr *)&addr, &len);
    printf("recv: %s\n", buff);
    close(fd);
    return 0;
}

