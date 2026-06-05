#include <my_header.h>

int main(int argc,char *argv[]){

    char str[20]="a/b/c/d";
    strtok(str,"/");
    //输出a
    printf("%s\n",str);
    char *p =NULL;
    while((p=strtok(NULL,"/"))){
        printf(" while  %s\n",p);
    }

    char ab_str[20]="/1/2/3/4";
    /* if(ab_str[0]=='/'){ */
    /*     strtok(ab_str,"/"); */
    /* } */
    /* printf("ab strtok  %s\n",ab_str); */

    char *ap=strtok(ab_str,"/");
    /* if(ap){ */
        printf("ab_first %s \n",ap);
    /* } */
    while((ap=strtok(NULL,"/"))){
        printf("while ab %s\n",ap);
    }

    return 0;
}

