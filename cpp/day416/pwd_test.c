#include <my_header.h>
int main(void){
    // 方式1：直接用栈数组作为getcwd返回值数组
    char path[1024] = {0};
    char *p = getcwd(path,sizeof(path));
    ERROR_CHECK(p,NULL,"getcwd");
    printf("cwd = %s\n", path);
    return 0;
}
