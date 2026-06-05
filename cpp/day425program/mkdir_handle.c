#include <my_header.h>
//查询文件是否存在
//存在就返回文件的id，不存在就返回-1
int select_id(MYSQL *conn,char *filename,int current_id){
    char select_sql[128]={0};
    snprintf(select_sql,sizeof(select_sql),"select id from files where name='%s' and parent_id=%d",filename,current_id);
    //查询
    int query = mysql_query(conn,select_sql);
    if(query != 0){
        printf("mysql_query failed. %s",mysql_error(conn));
        return -2;
    }
    MYSQL_RES *presult=mysql_store_result(conn);
    if(presult==NULL){
        return -2;
    }
    if(mysql_num_rows(presult)==0){
        printf("file not exist\n");
        mysql_free_result(presult);
        return -1;
    }
    MYSQL_ROW row=mysql_fetch_row(presult);
    if(row==NULL){
        printf("mysql_fetch_row. %s \n",mysql_error(conn));
        mysql_free_result(presult);
        return -2;
    }
    int file_id = -1;
    if(row[0]!=NULL){
        file_id=atoi(row[0]);
    }
    mysql_free_result(presult);

    return file_id;
}

//插入新的文件
int insert_file(MYSQL *conn,char *filename,int parent_id){
    char insert_sql[128]={0};
    snprintf(insert_sql,sizeof(insert_sql),"insert into files (name,parent_id,type,size,owner_id) values('%s',%d,1,0,1)",filename,parent_id);
    if(mysql_query(conn,insert_sql)!=0){
        printf("mysql_query failed %s\n",mysql_error(conn));
        return -1;
    }
    //获取本次连接最新一次插入数据的id
    int insert_id = mysql_insert_id(conn);
    if(insert_id==0){
        printf("mysql_insert_id failed.\n");
        return -1;
    }
    return insert_id;
}


void mkdir_dir(char *path){
    //连接数据库
    MYSQL *conn=mysql_init(NULL);
    if(mysql_real_connect(conn,"localhost","root","123456","cloud_test",0,NULL,0)==NULL){
        printf("mysql_real_connect failed. %s\n",mysql_error(conn));
        return;
    }
    
    //根据路径，定当前工作目录id
    int current_id = 0 ;
    char path_buff[128]={0};
    snprintf(path_buff,sizeof(path_buff),"%s",path);
    //如果绝对路径，就当前工作目录id就是1
    if(path_buff[0]=='/'){
        current_id=1;
    }else{
        //如果是相对路径，当前工作目录id就是2
        current_id=1;
    }

    //分割路径
    //第一次拆分
    char *p=strtok(path_buff,"/");
    //直到拆分完毕
    while(p!=NULL){
        printf("%s\n",p);
        //查找此目录是否存在，不存在则创建，存在则查找下一个目录
        int file_id = select_id(conn,p,current_id);
        //如果返回值是-1，说明不存在,需要创建这个目录
        if(file_id == -1){
            //将此文件插入
            current_id=insert_file(conn,p,current_id);
            //新插入的id如果是-1就返回，不是-1说明插入成功
            if(current_id != -1){
                printf("insert succes!\n");
            }else{
                mysql_close(conn);
                return;
            }
            //如果返回值是-2，说明错误，直接返回
        }else if (file_id==-2){
            mysql_close(conn);
            return;
            //其他情况说明查找成功
        }else{
            printf("dir is exist\n");
            current_id=file_id;
        }
        //每次拆分
        p=strtok(NULL,"/");
    }
    //关闭数据库连接
    mysql_close(conn);
}

int main(int argc,char *argv[]){
    char *path="a/b/c";
    mkdir_dir(path);

    return 0;
}