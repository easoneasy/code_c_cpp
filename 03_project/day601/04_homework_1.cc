#include <iostream>
#include <fstream>
#include <string>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFGlobal.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>

using namespace std;
using namespace protocol;

WFFacilities::WaitGroup waitGroup(1);

// 输出文件名
string g_filename;

void http_callback(WFHttpTask *task)
{
    int state = task->get_state();
    if(state != WFT_STATE_SUCCESS)
    {
        cerr << WFGlobal::get_error_string(state,task->get_error()) << endl;
        waitGroup.done();
        return;
    }

    HttpResponse *resp = task->get_resp();

    ofstream ofs(g_filename);

    if(!ofs)
    {
        cerr << "open file failed." << endl;
        waitGroup.done();
        return;
    }
    ofs << resp->get_http_version() << " "
        << resp->get_status_code() << " "
        << resp->get_reason_phrase() << "\r\n" ;
    
    HttpHeaderCursor cursor(resp);
    string name;
    string value;
    while(cursor.next(name,value))
    {
        ofs << name << " : " << value << "\r\n";
    }
    ofs << "\r\n" ;

    const void* body;
    size_t size;
    resp->get_parsed_body(&body,&size);
    ofs.write(static_cast<const char*>(body),size);
    ofs.close();
    
    cout << "save to " << g_filename << " success " << endl;
    waitGroup.done();

}

int main(int argc,char *argv[])
{
    if(argc != 3 )
    {
        cerr << "Usage : " << argv[0] << "<url><filename>" << endl;
        return -1;
    }

    string url = argv[1];
    g_filename = argv[2];
    WFHttpTask *task = WFTaskFactory::create_http_task(url,3,3,http_callback);
    HttpRequest *req = task->get_req();
    req->set_method("GET");
    req->set_header_pair("User-Agent","WorkflowWget");
    req->set_header_pair("Connection","Close");

    task->start();
    waitGroup.wait();

    return 0;
}