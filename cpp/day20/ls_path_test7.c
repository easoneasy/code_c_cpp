#include <my_header.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    DIR *dirp=opendir(argv[1]);
    ERROR_CHECK(dirp,NULL,"diropen failed.\n");

    struct dirent *dirent_p = NULL;
    struct stat *stat_p=(struct stat*)calloc(1,sizeof(struct stat));
    char path[100]={0};
    while((dirent_p=readdir(dirp))!=NULL){
        sprintf(path,"%s/%s",argv[1],dirent_p->d_name);
        int ret=stat(path,stat_p);
        ERROR_CHECK(ret,-1,"stat failed.\n");

        printf("%o %ld %d %d %ld %ld %s\n", stat_p->st_mode, stat_p->st_nlink, 
               stat_p->st_uid, stat_p->st_gid,
               stat_p->st_size, stat_p->st_mtime, 
               dirent_p->d_name);

    }



    return 0;
}

