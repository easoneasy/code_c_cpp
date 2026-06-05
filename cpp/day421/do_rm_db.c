#include <my_header.h>

int rm_db(int fd,char *path){
    //连接数据库
    MYSQL *conn_sql=mysql_init(NULL);
    if(mysql_real_connect(conn_sql,"localhost","root","123456","cloud_test",0,NULL,0)==NULL){
        send(fd,"mysql_real_connect failed",strlen("mysql_real_connect failed"),0);
        //printf("mysql_real_connect failed.%s\n",mysql_error(conn_sql));
        return -1;
    }
    //拆开路径
    char rm_buff[1024]={0};
    //当前父目录id
    int current_parent_id;
    //复制路径到一个数组中，方便遍历
        //------------------------------需要要删除的路径----------------------------------
    sprintf(rm_buff,"%s",path);
    if(rm_buff[0]=='/'){
        //把当前目录id设置为用户的根目录id
        //------------------------------需要根目录id----------------------------------
        current_parent_id=1;
    }else{
        //当前目录id
        //------------------------------需要当前目录id----------------------------------
        current_parent_id=2;
    }
    //设置一个指针，指向当前要查找的文件名
    char *start=rm_buff;
    //遍历路径数组
    //i的范围要是<= 这样可以遍历到最后一个字符
    for(size_t i =0;i<=strlen(rm_buff);i++){
        //如果当前字符是'/'或者'\0'，则表示前面一段是文件名
        //让start指针指向这段文件名，去查找
        if(rm_buff[i]=='/' || rm_buff[i]=='\0'){
            char current_path=rm_buff[i];
            rm_buff[i]='\0';
            //如果start指向\0说明后面没有文件名了，跳出循环
            //确保 start 指向的不是空字符串
            if(*start!='\0'){
                char select_buff[100]={0};
                sprintf(select_buff,"select id from file_info where parent_id=%d and name='%s'\n",current_parent_id,start);
                //执行查询语句
                mysql_query(conn_sql,select_buff);
                //获取查询结果
                MYSQL_RES *result =mysql_store_result(conn_sql);
                if(result==NULL){
                    send(fd,"mysql_store_result failed",strlen("mysql_store_result failed"),0);
                    return -1;
                }
                //从查询结果集中获取行
                MYSQL_ROW row = mysql_fetch_row(result);
                //获取失败，说明文件不存在
                if(row==NULL){
                    send(fd,"this file not exist",strlen("this file not exist"),0);
                    //释放结果集、断开数据库连接
                    mysql_free_result(result);
                    mysql_close(conn_sql);
                    return -1;
                }
                //将当前查询到的id作为下一次查询的父目录id
                current_parent_id=atoi(row[0]);
                //释放结果集
                mysql_free_result(result);
                if(current_path !='\0'){
                    rm_buff[i]='/';
                    start=&rm_buff[i+1];
                //如果已经到结尾了，就让start指向这里，结束
                }else{
            
                    start=&rm_buff[i];
                }
                //将文件名恢复，方便下一次循环
                rm_buff[i]='/';
                //将start指针指向/的后一个字符，相当于移动到下一段文件名
                start=&rm_buff[i+1];
            }
        }
    }
    if(current_parent_id!=0){
        char delete_buff[100]={0};
        sprintf(delete_buff,"delete from file_info where id=%d",current_parent_id);
        if(mysql_query(conn_sql,delete_buff)){
            send(fd,"mysql_query failed",strlen("mysql_query failed"),0);
            return -1;
        }
        send(fd,"delete success",strlen("delete success"),0);

        mysql_close(conn_sql);
    }
    return 0;
}
