#include <my_header.h>
void copy_by_path(const char *src_path,const char *dest_path,
                  char *buff,int buff_count){

    int src_fd = open(src_path,O_RDONLY);
    int dest_fd = open(dest_path,O_WRONLY|O_CREAT|O_TRUNC);
    ssize_t count =0;
    while((count=read(src_fd,buff,buff_count))!=0){
        write(dest_fd,buff,count);
    }
    close(src_fd);
    close(dest_fd);

}

long long current_time_millis(void) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts); // 获取当前时间
    return (long long)ts.tv_sec * 1000LL + ts.tv_nsec / 1000000; // 转换为毫秒
}
    
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);

    char *buff =(char *)malloc(20000);

    long long time1 = current_time_millis();
    copy_by_path(argv[1],argv[2],buff,1000);
    long long time2 = current_time_millis();
    copy_by_path(argv[1],argv[2],buff,4096);
    long long time3 = current_time_millis();
    
    printf("time2 - time1 = %lld\n",(time2-time1));
    printf("tiem3 - time2 = %lld\n",(time3-time2));

    return 0;
}

