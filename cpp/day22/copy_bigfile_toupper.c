#include <my_header.h>
#define ONCE_COPY_SIZE 1024*1024*16

long long current_time_millis(void) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts); // 获取当前时间
    return (long long)ts.tv_sec * 1000LL + ts.tv_nsec / 1000000; // 转换为毫秒
}

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int src_fp = open(argv[1],O_RDONLY);
    ERROR_CHECK(src_fp,-1,"src open failed.\n");

    int dest_fp = open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0666);
    ERROR_CHECK(dest_fp,-1,"dest open failed.\n");
    
    struct stat stat_buff;
    fstat(src_fp,&stat_buff);
    long total_size = stat_buff.st_size;   

    ftruncate(dest_fp,total_size);
    
    long copied_size=0;
    long long time1 = current_time_millis();
    while(copied_size<total_size){
        int cur_copy_size=(total_size-copied_size)>ONCE_COPY_SIZE ?
            ONCE_COPY_SIZE : (total_size-copied_size);
      char * src_mmap=(char *) mmap(NULL,cur_copy_size,PROT_READ,MAP_SHARED,src_fp,copied_size);
      ERROR_CHECK(src_mmap,MAP_FAILED,"src_mmap failed.\n");
      char * dest_mmap=(char *)mmap(NULL,cur_copy_size,PROT_READ|PROT_WRITE,MAP_SHARED,dest_fp,copied_size);
      ERROR_CHECK(dest_mmap,MAP_FAILED,"dest_mmap failed.\n");

      for(int i=0;i<cur_copy_size;i++){
          dest_mmap[i]=toupper(dest_mmap[i]);
      }
    
      memcpy(dest_mmap,src_mmap,cur_copy_size);
      munmap(src_mmap,cur_copy_size);
      munmap(dest_mmap,cur_copy_size);
      copied_size+=cur_copy_size;
    }
    long long time2 = current_time_millis();
    printf("time2 - time1 = %lld\n",time2-time1);
    close(src_fp);
    close(dest_fp);

    return 0;
}

