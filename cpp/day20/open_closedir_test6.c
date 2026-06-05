#include <my_header.h>

int main(int argc,char *argv[])
{
    //打开目录
    DIR *dirp=opendir("/home/zyt/day18");
    ERROR_CHECK(dirp,NULL,"opendir failed.\n");
    //使用
    struct dirent *dirent_p =NULL;
    while((dirent_p=readdir(dirp))!=NULL){
        
    printf("%ld %s %ld %d %d\n",dirent_p->d_ino,dirent_p->d_name,
           dirent_p->d_off,dirent_p->d_reclen,dirent_p->d_type );
    }
    printf("DT_REG =%d\n",DT_REG);
    printf("DT_DIR =%d\n",DT_DIR);

    closedir(dirp);


    return 0;
}

