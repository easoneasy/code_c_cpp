#include <iostream>
#include <signal.h>
#include <vector>
#include <workflow/MySQLMessage.h>
#include <workflow/MySQLResult.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFGlobal.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/mysql_types.h>

using namespace std;
using namespace protocol;

WFFacilities::WaitGroup waitGroup(1);

void sig_handler(int)
{
    waitGroup.done();
}

//不同系统的类型适配
void display_cell(const MySQLCell &cell)
{
    if(cell.is_null()){
        cout << "(NULL)" ;
    }else if(cell.is_int()){
        cout << cell.as_int();
    }else if(cell.is_ulonglong()){
        cout << cell.as_ulonglong();
    }else if(cell.is_float()){
        cout << cell.as_float();
    }else if(cell.is_double()){
        cout << cell.as_double();
    }else if(cell.is_string()){
        cout << cell.as_string();
    }else if(cell.is_date()){
        cout << cell.as_date();
    }else if(cell.is_time()){
        cout << cell.as_time();
    }else if(cell.is_datetime()){
        cout << cell.as_datetime();
    }
}

void mysql_callback(WFMySQLTask *task)
{
    // 1、判断任务的状态
    int state = task->get_state();
    if(state != WFT_STATE_SUCCESS)
    {
        cerr << WFGlobal::get_error_string(state,task->get_error()) << endl;
        return;
    }

    // 2、判断最后一个返回包的类型
    MySQLResponse *resp = task->get_resp();
    if(resp->get_packet_type() == MYSQL_PACKET_ERROR)
    {
        cerr << "error code : " << resp->get_error_code()
            << " , error msg : " << resp->get_error_msg() << endl;
        return;
    }

    // 3、处理结果集
    MySQLResultCursor cursor(resp);
    if(cursor.get_cursor_status() == MYSQL_STATUS_GET_RESULT)
    {
        cout << "fileds : " << cursor.get_field_count() << endl;
        cout << "rows : " << cursor.get_rows_count() << endl;
        // 遍历输出所有的记录
        vector<MySQLCell> record;
        while(cursor.fetch_row(record))
        {
            // 成功获取一条记录
            for(const MySQLCell & cell: record)
            {
                display_cell(cell);
                cout << "\t";
            }
            cout << endl;
        }
    }
}

int main(int argc,char *argv[])
{
    // 注册信号
    signal(SIGINT,sig_handler);

    // 1、创建MySQL任务
    WFMySQLTask *task = WFTaskFactory::create_mysql_task
    (
        "mysql://root:123456@localhost:3306/demo",
        3,
        mysql_callback
    );

    // 2、设置任务参数
    string sql = "select * from tbl_user";
    MySQLRequest *req = task->get_req();
    req->set_query(sql);

    // 3、启动任务
    task->start();
    // 4、等待任务结束
    waitGroup.wait();

    return 0;
}

