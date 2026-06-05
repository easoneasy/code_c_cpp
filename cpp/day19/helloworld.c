#include <my_header.h>
void copy_file(const char *src_path,const char *dest_path){
    FILE *src_fp=fopen(src_path,"r");
    /* /1* if(src_fp==NULL){ *1/ */
    /*     /1* printf("src open failed.\n"); *1/ */
    /*     /1* return ; *1/ */
    /* /1* } *1/ */
    ERROR_CHECK(src_fp,NULL,"src open failed");

    FILE *dest_fp=fopen(dest_path,"w");
    /* if(dest_fp==NULL){ */
    /*     printf("dest open failed.\n"); */
    /*     fclose(src_fp); */
    /*     return; */
    /* } */
    ERROR_CHECK(dest_fp,NULL,"dest openfailed");

    int ch;
    while((ch=fgetc(src_fp))!=EOF){
        fputc(ch,dest_fp);
    }
    fclose(src_fp);
    fclose(dest_fp);
}

int main(int argc,char *argv[])
{
    /* if(argc!=3){ */
    /*     printf("argc number error.\n"); */
    /* } */
    
    ARGS_CHECK(argc,3);
    copy_file(argv[1],argv[2]);


    return 0;
}

