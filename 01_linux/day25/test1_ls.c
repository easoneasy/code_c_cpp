#include <my_header.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    DIR  *dirp=opendir(argv[1]);
    ERROR_CHECK(dirp,NULL,"open dir failed.\n");
    
    struct dirent *dirent_p=NULL;
    struct stat *stat_p = (struct stat*)calloc(1,sizeof(struct stat));
    while((dirent_p=readdir(dirp))!=NULL){
        int ret = stat(dirent_p->d_name,stat_p);
        ERROR_CHECK(ret,-1,"stat failed.\n");
        printf("%o %ld %d %d %ld %ld %s\n",stat_p->st_mode,stat_p->st_nlink,
               stat_p->st_uid,stat_p->st_gid,stat_p->st_size,
               stat_p->st_mtim.tv_sec,dirent_p->d_name);
    }
    closedir(dirp);


    return 0;
}

