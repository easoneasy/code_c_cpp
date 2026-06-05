#include <my_header.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    DIR *dirp = opendir(argv[1]);
    ERROR_CHECK(dirp,NULL,"dirp open failed.\n");
    
    struct dirent *dirent_p =NULL;
    long loc;
    while((dirent_p = readdir(dirp))!=NULL){
        printf("%ld %s %d %d\n",dirent_p->d_ino,dirent_p->d_name,
               dirent_p->d_reclen,dirent_p->d_type);
        if(strcmp("1.txt",dirent_p->d_name)==0){
            loc=telldir(dirp);
        }
    }

    printf("----------------------------\n");
    seekdir(dirp,loc);
    dirent_p=readdir(dirp);

    printf("%ld %s %d %d\n",dirent_p->d_ino,dirent_p->d_name,
           dirent_p->d_reclen,dirent_p->d_type);
    closedir(dirp);

    return 0;
}

