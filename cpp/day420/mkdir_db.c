#include <my_header.h>

int  mkdir_db(char *path){
    //初始化数据库连接
    MYSQL *conn_sql=mysql_init(NULL);
    if(conn_sql==NULL){
        printf("mysql_init,%s\n",mysql_error(conn_sql));
        return -1;
    }
    MYSQL *p =mysql_real_connect(conn_sql,"localhost","root","123456","cloud_test",0,NULL,0);
    if(p==NULL){
        printf("mysql_real_connect failed,%s\n",mysql_error(conn_sql));
        return -1;
    }
    printf("mysql_real_connect success\n");
    //当前父目录id（当前工作路径）
    int current_parent_id=2;
    //将给定路径拆开
    char mkdir_path[1024]={0};
    strncpy(mkdir_path,path,strlen(path));
    printf("init mkdir_path:%s\n",mkdir_path);
    //设置一个指针，指向当前要查找的文件名
    char *start=mkdir_path;
    for(int i=0;i<=strlen(mkdir_path);i++){
        //如果当前字符是'/'或者'\0'，则表示当前字符是文件名
        //但是会遇到一个问题，就是会让for循环中i的范围有些模糊，可能会产生越界问题
        if(mkdir_path[i]=='/' || mkdir_path[i]=='\0'){
            mkdir_path[i]='\0';
            printf("start : %s\n",start);
            //加一个判断，如果start不为空，就可以继续查，如果start为空，说明查完了，解决越界问题
            if (*start != '\0'){
                //查询当前路径是否存在
                char select_path[256];
                sprintf(select_path,"select id from file_info where parent_id=%d and name='%s'",current_parent_id,start);
                int query_ret  = mysql_query(conn_sql,select_path);
                //返回值为0，表示执行成功，与查询结果无关
                if(query_ret!=0){
                    //执行失败
                    printf("mysql_query failed.%s\n",mysql_error(conn_sql));
                    return -1;
                }
                //获取查询结果
                //mysql_store_result()返回结果集指针，结果集指针非空表示查询成功
                MYSQL_RES *result = mysql_store_result(conn_sql);
                if(result == NULL){
                    //查询结果为空
                    printf("mysql_store_result failed.%s\n",mysql_error(conn_sql));
                    return -1;     
                }
                if(mysql_num_rows(result) == 0){
                    //路径不存在
                    printf("path not exists:%s\n",start);
                    //需要向数据库表中插入新的数据
                    char insert_path[256];
                    sprintf(insert_path,"insert into file_info (name,parent_id,file_mode) values('%s',%d,1)",start,current_parent_id);
                    mysql_query(conn_sql,insert_path);
                    //获取新增数据的id
                    int insert_ret=mysql_insert_id(conn_sql);
                    if(insert_ret==0){
                        //未自增，获取自增id失败
                        printf("mysql_insert_id failed.%s\n",mysql_error(conn_sql));
                    }else{
                        //获取新目录id成功，将此id作为查找下一次查找的父目录id
                        printf("insert_id:%d\n",insert_ret);
                        current_parent_id=insert_ret;
                        printf("current_parent_id:%d\n",current_parent_id);

                    }
                }else{
                    //查询结果不为空，目录存在，继续查子目录是否存在
                    printf("path exists:%s\n",start);   
                    //获取查到数据的id，作为下一次查找的父目录id         
                    MYSQL_ROW row=mysql_fetch_row(result);
                    if(row == NULL){
                        mysql_free_result(result);
                        return -1;
                    }
                    //将查到的目录的id赋值给current_parent_id
                    current_parent_id=atoi(row[0]);
                    printf("current_parent_id:%d\n",current_parent_id);
                }
                //将文件名恢复，方便下一次循环
                mkdir_path[i]='/';
                start=&mkdir_path[i+1];
                //释放结果集
                mysql_free_result(result);
            }

        }

    }
    

    return 0;
}


int main(int argc,char *argv[]){
    mkdir_db(argv[1]);
    printf("mkdir_db %s\n",argv[1]);

    return 0;
}

