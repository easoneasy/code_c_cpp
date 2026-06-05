#include <my_header.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    DIR *dirp=opendir(argv[1]);
    ERROR_CHECK(dirp,NULL,"dir open failed.\n");

    struct dirent *dirent_p=NULL;
    
    while((dirent_p=readdir(dirp))!=NULL){
        printf("%ld %s %ld %d %d\n",dirent_p->d_ino,dirent_p->d_name,
               dirent_p->d_off,dirent_p->d_reclen,dirent_p->d_type);
    }


    return 0;
}

