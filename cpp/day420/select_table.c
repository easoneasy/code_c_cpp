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
                                "cloud_test",0,NULL,0);
    if(p==NULL){
        printf("mysql_real_connect failed. %s\n",mysql_error(conn_sql));
        return -1;
    }
    printf("mysql_real_connect success.\n");
    //查询语句
    //第一轮查找需要需要找的文件的id
    //剩下就查找父目录id
    char *target_filename="a";
    char first_sql[256];
    sprintf(first_sql,"select id from file_info where name='%s'and parent_id = 2",target_filename);
    int ret = mysql_query(conn_sql,first_sql);
    if(ret!=0){
        printf("mysql_query first failed.%s\n",mysql_error(conn_sql));
        mysql_close(conn_sql);
        return -1;
    }
    MYSQL_RES *first_ret = mysql_store_result(conn_sql);
    if(!first_ret){
        printf("mysql_store_result first failed.%s\n",mysql_error(conn_sql));
        mysql_close(conn_sql);
        return -1;
    }
        MYSQL_ROW row=mysql_fetch_row(first_ret);
        if(row == NULL){
            mysql_free_result(first_ret);
            return -1;
        }
        int current_id=atoi(row[0]);
        mysql_free_result(first_ret);


    char path_buff[1024]={0};
    char temp[1024]={0};
    while(current_id !=-1){
        char query_sql[256];
        sprintf(query_sql,"select name,parent_id from file_info where id = %d",current_id);

        int ret = mysql_query(conn_sql,query_sql);
        if(ret!=0){
            printf("mysql_query failed.%s\n",mysql_error(conn_sql));
            return -1;
        }
        //获取查询结果
        MYSQL_RES *pres = mysql_store_result(conn_sql);
        if(!pres){
            printf("mysql_store_result failed.\n");
            return -1;
        }
        //获取行
        MYSQL_ROW row=mysql_fetch_row(pres);
        if(row == NULL){
            mysql_free_result(pres);
            return -1;
        }

        //
        current_id = atoi(row[1]);
        if(path_buff[0]==0){
            sprintf(temp,"%s",row[0]);
            strcpy(path_buff,temp);
        }else{
            /* sprintf(temp,"%s/%s",row[0],path_buff); */
            snprintf(temp, sizeof(temp), "%s/%s", row[0], path_buff);
            strcpy(path_buff,temp);
        }
        mysql_free_result(pres);

    }
    printf("%s\n",path_buff);
        mysql_close(conn_sql);

    return 0;
}

