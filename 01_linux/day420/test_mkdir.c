
#include<my_header.h>

//连接数据库
MYSQL *get_db(){
    MYSQL *conn=mysql_init(NULL);
    if(mysql_real_connect(conn,"localhost","root","123456","cloud_test",0,NULL,0)==NULL){
        printf("mysql_real_init failed.\n");
        return NULL;
    }
    //数据库连接成功
    return conn;
}

//根据文件查找id
int get_id(int current_parent_id,char *start,MYSQL *conn){
    
    char select_path[128]={0};
    sprintf(select_path,"select id from file_info where parent_id=%d and name='%s'",current_parent_id,start);
    //数据库查询语句
    mysql_query(conn,select_path);

    MYSQL_RES *result=mysql_store_result(conn);
    if(result==NULL){
        //要么没查到，要么查找错误
        printf("the file not exsit");
        return current_parent_id;
    }
    //查到了，更新id
    MYSQL_ROW row=mysql_fetch_row(result);
    if(row==NULL){
        printf("not exsit");
        return -1;
    }
    current_parent_id=atoi(row[0]);
    mysql_free_result(result);
    return current_parent_id;
}

//新建
int mkdir_db(int current_parent_id,MYSQL *conn, char *start){
    char mkdir_buf[1024]={0};
    sprintf(mkdir_buf,"insert into file_info (name,parent_id,file_mode) values('%s',%d,1)",start,current_parent_id);
    mysql_query(conn,mkdir_buf);
    //获取新增数据的id
    int insert_ret=mysql_insert_id(conn);
    if(insert_ret==0){
        //未自增，获取自增id失败
        printf("mysql_insert_id failed.%s\n",mysql_error(conn));
    }else{
        //获取新目录id成功，将此id作为查找下一次查找的父目录id
        current_parent_id=insert_ret;
        printf("------current_parent_id : %d\n",current_parent_id);
    }
    return current_parent_id;

}

int get_id_by_path(char *path){
    //数据库连接
    MYSQL *conn = get_db();
    if(path ==NULL){
        return -1;

    }
    int current_parent_id;
    char path_buf[1024]={0};
    snprintf(path_buf,strlen(path_buf),"%s",path);
    char *start=path_buf;
    if(path_buf[0]=='/'){
        //说明是绝对路径，需要用户的父目录id
        current_parent_id=1;
    }else{
        //当前工作目录的id
        current_parent_id=3;
    }
    //切分路径
    for(size_t i=0;i<=strlen(path_buf);i++){
        if(path_buf[i]=='/' || path_buf[i]=='\0'){
            char current_char = path_buf[i];
            //截断
            path_buf[i]='\0';

            if(*start != '\0'){
                //截断的部分（需要找的文件名）
                //返回当前父目录的id
                current_parent_id=get_id(current_parent_id,start,conn);
                printf("%d\n",current_parent_id);
                //返回了有效的父目录id
                mkdir_db(current_parent_id,conn,start);
            }
            //如果没到字符串真正的结尾，才移动start指针
            if(current_char !='\0'){
                path_buf[i]='/';
                start=&path_buf[i+1];
            //如果已经到结尾了，就让start指向这里，结束
            }else{
            
                start=&path_buf[i];
            }
        }
    }
    return 0;
}

int main(int argc,char *argv[]){
    get_id_by_path(argv[1]);
    return 0;
}
