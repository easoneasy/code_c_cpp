#include <my_header.h>
#define QUERY_SIZE 1024
void handle_ls(int current_id){
    //数据库连接
    MYSQL *conn=mysql_init(NULL);
    MYSQL *real_p=mysql_real_connect(conn,"localhost","root","123456","cloud_test",0,NULL,0);
    if(real_p==NULL){
        printf("mysql_real_connect failed.\n");
        return;
    }
    printf("mysql_real_connect success!\n");

    char select_buff[QUERY_SIZE]={0};
    snprintf(select_buff,sizeof(select_buff),"select name,type,size from files where id=%d",current_id);
    if(mysql_query(conn,select_buff)){
        printf("mysql_query failed.\n");
        return;
    }
    printf("mysql_query success!\n");
    MYSQL_RES *presult = mysql_store_result(conn);
    if(presult==NULL){
        printf("mysql_store_result failed.\n");
        mysql_free_result(presult);
        return;
    }
    printf("mysql_store_result success!\n");
    MYSQL_ROW row;
    //获取每行的数据
    while(row=mysql_fetch_row(presult)){
        for(size_t i=0;i<mysql_num_fields(presult);i++){
            printf("%s\t",row[i]);
        }
    }
    printf("\n");
    //释放资源
    mysql_free_result(presult);
    mysql_close(conn);

}


int main(int argc,char *argv[]){

handle_ls(2);

    return 0;
}

