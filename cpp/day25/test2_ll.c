#include <my_header.h>
void mode_file(mode_t mode,char *type_and_mode){
    char file_type = '?';
    switch (mode & S_IFMT) {
    case S_IFBLK:  file_type='b';            	break;
    case S_IFCHR:  file_type='c';        		break;
    case S_IFDIR:  file_type='d';               break;
    case S_IFIFO:  file_type='p';               break;
    case S_IFLNK:  file_type='l';               break;
    case S_IFREG:  file_type='-';            	break;
    case S_IFSOCK: file_type='s';               break;
    default:       file_type='?';               break;
    }
    type_and_mode[0]=file_type;

    type_and_mode[1]=((mode&0400)!=0)? 'r':'-';
    type_and_mode[2]=((mode&0200)!=0)? 'w':'-';
    type_and_mode[3]=((mode&0100)!=0)? 'x':'-';

    type_and_mode[4]=((mode&0040)!=0)? 'r':'-';
    type_and_mode[5]=((mode&0020)!=0)? 'w':'-';
    type_and_mode[6]=((mode&0010)!=0)? 'x':'-';

    type_and_mode[7]=((mode&0004)!=0)? 'r':'-';
    type_and_mode[8]=((mode&0002)!=0)? 'w':'-';
    type_and_mode[9]=((mode&0001)!=0)? 'x':'-';
    type_and_mode[10]='\0';
}
void parse_time_to_str(time_t sec,char *str){
    struct tm *tm_ret=localtime(&sec);
    sprintf(str,"%d-%02d-%02d %02d:%02d:%02d",
            tm_ret->tm_year+1900,tm_ret->tm_mon+1,tm_ret->tm_mday,
            tm_ret->tm_hour,tm_ret->tm_min,tm_ret->tm_sec);
}
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    DIR *dirp = opendir(argv[1]);
    ERROR_CHECK(dirp,NULL,"dirp failed.\n");

    struct dirent *direntp =NULL;
    struct stat *statp=(struct stat*)calloc(1,sizeof(struct stat));
    while((direntp=readdir(dirp))!=NULL){
        int ret = stat(direntp->d_name,statp);
        ERROR_CHECK(ret,-1,"stat filed.\n");
        
        char type_and_mode[20]={0};
        mode_file(statp->st_mode,type_and_mode);

        char str[100]={0};
        parse_time_to_str(statp->st_mtim.tv_sec,str);
        printf("%s %ld %s %s %ld %s %s\n",type_and_mode,statp->st_nlink,
               getpwuid(statp->st_uid)->pw_name,getgrgid(statp->st_gid)->gr_name,
               statp->st_size,str,direntp->d_name);
    }
    closedir(dirp);


    return 0;
}

