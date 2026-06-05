#include <my_header.h>

int main(int argc,char *argv[])
{
    printf("---------\n");
    int fd = open("222.txt", O_WRONLY | O_TRUNC);
    ERROR_CHECK(fd, -1, "open failed");

    printf("11111\n");

    int stdout_backup_fd = dup(STDOUT_FILENO);
    close(STDOUT_FILENO);
    dup(fd);
    printf("22222\n");

    close(STDOUT_FILENO);
    dup(stdout_backup_fd);
    printf("33333\n");

    close(STDOUT_FILENO);
    dup(fd);
    printf("44444\n");
    close(STDOUT_FILENO);
    dup(stdout_backup_fd);
    printf("55555\n");

    close(fd);
    close(stdout_backup_fd);
    close(STDOUT_FILENO);


    return 0;
}

