#include <my_header.h>
void copy_big_file(int srcp,int destp,char *buff,long buff_count ,ssize_t count){
    while((count = read(srcp,buff,buff_count))!=0){
        write(destp,buff,count);

    }
}
long long current_time_millis(void) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts); // 获取当前时间
    return (long long)ts.tv_sec * 1000LL + ts.tv_nsec / 1000000; // 转换为毫秒
}

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int srcp=open(argv[1],O_RDONLY);
    ERROR_CHECK(srcp,-1,"src open failed.\n");
    int destp=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC);
    ERROR_CHECK(destp,-1,"dest openfailed.\n");

    char buff[4096]={0};
    ssize_t count=0;
    long long time1 = current_time_millis();
    copy_big_file(srcp,destp,buff,sizeof(buff),count);
    long long time2 = current_time_millis();
    printf("time2 - time1 = %lld\n",time2-time1);
    return 0;
}

