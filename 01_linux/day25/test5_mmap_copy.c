#include <my_header.h>
#define ONCECPSIZE 1024*1024*16

long long current_time_millis(void) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts); // 获取当前时间
    return (long long)ts.tv_sec * 1000LL + ts.tv_nsec / 1000000; // 转换为毫秒
}
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int srcp = open(argv[1],O_RDONLY);
    ERROR_CHECK(srcp,-1,"src open failed.\n");
    int destp = open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0666);
    ERROR_CHECK(destp,-1,"dest open failed.\n");

    ssize_t copied_size = 0;
    struct stat statbuff;
    fstat(srcp,&statbuff);
    long src_size = statbuff.st_size;
    ftruncate(destp,src_size);
    long time1=current_time_millis();
    while(copied_size<src_size){
        int cur_size = (src_size-copied_size)>ONCECPSIZE ? ONCECPSIZE : (src_size-copied_size);

        char *src_cp = (char *)mmap(NULL,cur_size,PROT_READ,MAP_SHARED,srcp,copied_size);
        ERROR_CHECK(src_cp,MAP_FAILED,"mmap src failed.\n");
        char *dest_cp =(char *)mmap(NULL,cur_size,PROT_READ|PROT_WRITE,MAP_SHARED,destp,copied_size);
        ERROR_CHECK(dest_cp,MAP_FAILED,"mmap dest failed.\n");

        memcpy(dest_cp,src_cp,cur_size);
        munmap(src_cp,cur_size);
        munmap(dest_cp,cur_size);
        
        copied_size+=cur_size;
    }
    long time2=current_time_millis();
    printf("time2 - time1 =%ld\n",time2-time1);
    close(srcp);
    close(destp);


    return 0;
}

