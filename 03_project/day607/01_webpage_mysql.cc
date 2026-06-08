#include <cstddef>
#include <iostream>
#include <string>
#include <workflow/HttpMessage.h>
#include <workflow/MySQLMessage.h>
#include <workflow/MySQLResult.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFGlobal.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>
#include <workflow/mysql_types.h>

using namespace std;
using namespace protocol;

struct SeriesContex
{
    string url;
    size_t size;
    bool success;
};

void mysql_callback(WFMySQLTask *mysqlTask)
{
    int state = mysqlTask->get_state();
    if(state != WFT_STATE_SUCCESS)
    {
        cerr << WFGlobal::get_error_string(state, mysqlTask->get_error());
        return;
    }
    MySQLResponse *resp = mysqlTask->get_resp();
    if(resp->get_packet_type() == MYSQL_PACKET_ERROR)
    {
        cerr << resp->get_error_code() << " "
            << resp->get_error_msg() << endl;
        return;
    }
    SeriesWork *series = series_of(mysqlTask);
    SeriesContex *ctx = static_cast<SeriesContex *>(series->get_context());
    ctx->success = true;
    MySQLResultCursor cursor(resp);
    cout << "插入记录： id = " << cursor.get_insert_id() << endl;
}

void http_callback(WFHttpTask *httpTask)
{
    int state = httpTask->get_state();
    if(state != WFT_STATE_SUCCESS)
    {
        cerr << WFGlobal::get_error_string(state, httpTask->get_error()) <<endl;
        return;
    }

    SeriesWork *series = series_of(httpTask);
    SeriesContex *ctx = static_cast<SeriesContex*>(series->get_context());

    HttpResponse *resp = httpTask->get_resp();
    const void *body;
    size_t size;
    resp->get_parsed_body(&body, &size);
    ctx->size = size;

    WFMySQLTask *mysqlTask = WFTaskFactory::create_mysql_task
        (
            "mysql://root:123456@localhost:3306",
            3,
            mysql_callback
        );

    string url = static_cast<char*>(httpTask->user_data);
    string sql = "insert into tbl_webpage (url,size) values ('"
        + url + "',"
        + to_string(size) + ")";
    cout << "[SQL]" << sql << endl;

    MySQLRequest *mysql_req = mysqlTask->get_req();
    mysql_req->set_query(sql);

    series->push_back(mysqlTask);
}

int main(int argc,char *argv[])
{
    if(argc != 2)
    {
        cerr << "Usage : " << argv[0] << "<URL>" << endl;
    }

    WFHttpTask *httpTask = WFTaskFactory::create_http_task
        (
            argv[1],3,3,http_callback
        );
    httpTask->user_data = argv[1];

    HttpRequest *req = httpTask->get_req();
    req->add_header_pair("Accept","*/*");
    req->add_header_pair("User-Agent","wget/1.14(Linux-gnu)");
    req->add_header_pair("Connection","close");

    HttpResponse *resp = httpTask->get_resp();
    resp->set_size_limit(20 * 1024 * 1024);
    httpTask->set_receive_timeout(30 * 1000);

    WFFacilities::WaitGroup waitGroup(1);

    SeriesWork *series = Workflow::create_series_work(httpTask,[&waitGroup]
        (const SeriesWork *series)
        {
            SeriesContex *ctx = static_cast<SeriesContex*>(series->get_context());
            if(ctx->success)
            {
                cout << "success" << endl;
            }else{
                cout << "failed" << endl;
            }
            delete ctx;
            waitGroup.done();
        });
    SeriesContex *ctx = new SeriesContex{argv[1],0,false};
    series->set_context(ctx);
    series->start();
    waitGroup.wait();

    return 0;
}
