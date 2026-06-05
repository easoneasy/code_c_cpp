#include <my_header.h>
int main(int argc,char *argv[]){
    //初始化
    MYSQL *conn_sql= mysql_init(NULL);
    if(conn_sql==NULL){
        printf("mysql_init failed.\n");
        return -1;
    }
    printf("mysql_init success.\n");
    //连接数据库
    MYSQL *p=mysql_real_connect(conn_sql,"localhost","root","123456",
                                "userdata",0,NULL,0);
    if(p==NULL){
        printf("mysql_real_connect failed. %s\n",mysql_error(conn_sql));
        return -1;
    }
    printf("mysql_real_connect success.\n");
    //查询语句
    int ret = mysql_query(conn_sql,"select * from student");
    if(ret!=0){
        printf("mysql_query failed.\n");
        return -1;
    }
    //获取查询结果
    MYSQL_RES *pres = mysql_store_result(conn_sql);
    if(!pres){
        printf("mysql_store_result failed.\n");
        return -1;
    }
    //获取行
    MYSQL_ROW row;
    while((row = mysql_fetch_row(pres))){
        for(int i=0;i<mysql_num_fields(pres);i++){
            printf("%s\t\t",row[i]);
        } 
        printf("\n");
    }
    mysql_free_result(pres);
    mysql_close(conn_sql);

    return 0;
}

