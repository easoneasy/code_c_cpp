#include <iostream>
#include <string>
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

void mysql_callback(WFMySQLTask* task)
{
    // 1、判断任务的状态
    int state = task->get_state();
    if(state != WFT_STATE_SUCCESS)
    {
        cerr << WFGlobal::get_error_string(state,task->get_error()) << endl;
        waitGroup.done();
        return;
    }

    // 2、任务成功，收到响应了：判断返回包的类型
    MySQLResponse *resp = task->get_resp();
    if(resp->get_packet_type() == MYSQL_PACKET_ERROR)
    {
        cerr << "error code : " << resp->get_error_code()
            << " , error msg : " << resp->get_error_msg() << endl;
        waitGroup.done();
        return;
    }
    // 3、DML：处理结果集
    MySQLResultCursor cursor(resp);
    if(cursor.get_cursor_status() == MYSQL_STATUS_OK)
    {
        unsigned long long rows = cursor.get_affected_rows();
        unsigned long long id = cursor.get_insert_id();
        cout << "affected rows : " << rows
            << " , inserted id : " << id << endl;
    }
    waitGroup.done();
}

int main(int argc,char *argv[])
{
    // 1、创建MySQL任务
    WFMySQLTask* task = WFTaskFactory::create_mysql_task
    (
        "mysql://root:123456@localhost:3306/demo",
        3,
        mysql_callback
    );
    // 2、设置任务的参数
    MySQLRequest *req = task->get_req();
    string sql = "insert into tbl_user (username,password,salt) values ('Jo',123,'h')";
    req->set_query(sql);
    // 3、启动任务
    task->start();
    // 4、等待任务执行完毕
    waitGroup.wait();

    return 0;
}

