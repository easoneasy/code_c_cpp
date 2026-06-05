#include<my_header.h>
//连接数据库
MYSQL *connect_mysql(){
    MYSQL *conn=mysql_init(NULL);
    if(mysql_real_connect(conn,"localhost","root","123456","cloud_test",0,NULL,0)==NULL){
        printf("mysql_real_connect failed. %s\n",mysql_error(conn));
        return NULL;
    }
    return conn;
}

//递归删除
void rm_files_and_dir(MYSQL *conn,int target_id){
    //找id为target_id的文件/目录
    //需要知道目标id是文件还是目录
    char select_sql[256]={0};
    snprintf(select_sql,sizeof(select_sql),"select name,type,hash from files where id = %d",target_id);
    if(mysql_query(conn,select_sql)!=0){
        printf("select query failed. %s\n",mysql_error(conn));
        return;
    }
    //获取结果集
    MYSQL_RES *presult=mysql_store_result(conn);
    //获取结果集失败
    if(presult==NULL){
        printf("mysql_store_feiled failed. %s\n",mysql_error(conn));
        mysql_free_result(presult);
        return;
    }
    //获取结果集的行
    MYSQL_ROW row = mysql_fetch_row(presult);
    if(row==NULL){
        printf("mysql fetch field failed. %s \n",mysql_error(conn));
        mysql_free_result(presult);
        return ;
    }
    //保存文件数据
    char file_name[20]={0};
    snprintf(file_name,sizeof(file_name),"%s",row[0]);
    char file_type[20]={0};
    snprintf(file_type,sizeof(file_type),"%s",row[1]);
    char file_hash[128]={0};
    snprintf(file_hash,sizeof(file_hash),"%s",row[2]);
    //释放结果集
    mysql_free_result(presult);

    //判断文件类型  0是文件，1是目录
    if(strcmp(file_type,"0")==0){
        printf("files \n");
        //是文件，先根据hash值查找是否有别的文件使用此hash
        //如果有就只删除数据库中的文件，如果没有就ulink删除本地文件
        char hash_sql[256]={0};
        snprintf(hash_sql,sizeof(hash_sql),"select id from files where hash='%s'",file_hash);
        if(mysql_query(conn,hash_sql)!=0){
            //查询失败
            printf("hash query failed. %s \n",mysql_error(conn));
            return ;
        }
        //获取结果集
        MYSQL_RES *hash_result=mysql_store_result(conn);
        if(hash_result==NULL){
            printf("hash_result failed. %s \n",mysql_error(conn));
            mysql_free_result(hash_result);
            return;
        }
        //获取结果集中的行
        MYSQL_ROW row = mysql_fetch_row(hash_result);
        if(row==0){
            printf("hash row is null %s \n",mysql_error(conn));
            mysql_free_result(hash_result);
            return;
        }
        //没有其他文件使用hash,删除本地文件
        if(mysql_num_rows(hash_result)==1){
            //删除本地文件
            //unlink();
        }
        mysql_free_result(hash_result);
        //有其他文件使用相同hash，不删除本地文件
        char delete_sql[256]={0};
        snprintf(delete_sql,sizeof(delete_sql),"delete from files where id=%d ",target_id);
        if(mysql_query(conn,delete_sql)!=0){
            printf("delete mysql query failed.%s \n",mysql_error(conn));
            return;
        }
        int affected = mysql_affected_rows(conn);
        if(affected>0){
            printf("delete success!!\n");
        }else{
            printf("not the file.\n");
        }
    }else if(strcmp(file_type,"1")==0){
        //是目录
        printf("dirctory.\n");
        char select_child_sql[256]={0};
        snprintf(select_child_sql,sizeof(select_child_sql),"select id from files where parent_id = %d",target_id);
        if(mysql_query(conn,select_child_sql)!=0){
            printf("child dir select failed. %s \n",mysql_error(conn));
            return;
        }
        //获取结果集

    }
    

    
}

//删除入口函数
void rm_files(char *path){
    //连接数据库
    MYSQL *conn = connect_mysql();
    
    //将路径拷贝到字符数组中
    char rm_path[128]={0};
    snprintf(rm_path,sizeof(rm_path),"%s",path);

    //获取当前工作目录
    int current_parent_id;
    if(rm_path[0]=='/'){
        current_parent_id=0;
    }else{
        current_parent_id=1;
    }

    //执行删除逻辑
    
}



int main(int args,char argv[]){

}