#include <stdio.h>
#include <string.h>
void func(char *start){
    printf("%s\n",start);
}
void current_find_file(char *path) {
    if (path == NULL) return; // 安全检查

    char path_buff[1024] = {0};
    strncpy(path_buff, path, strlen(path)); // 使用 strncpy 更安全

    char *start = path_buff;
    int len = strlen(path_buff);

    for (int i = 0; i <= len; i++) {
        if (path_buff[i] == '/' || path_buff[i] == '\0') {
            // 记住当前的字符，如果是 \0 说明到头了
            char current_char = path_buff[i]; 
            
            path_buff[i] = '\0'; // 截断
            
            if (*start != '\0') {
                //回调函数，将start传给函数
                func(start);
            }

            // 如果还没到字符串真正的结尾，才移动 start 指针
            if (current_char != '\0') {
                path_buff[i] = '/'; // 还原，方便调试或后续使用
                start = &path_buff[i + 1];
            } else {
                // 如果已经到了 \0，就让 start 指向这里并结束
                start = &path_buff[i]; 
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("用法: %s <路径>\n", argv[0]);
        return -1;
    }
    current_find_file(argv[1]);
    return 0;
}