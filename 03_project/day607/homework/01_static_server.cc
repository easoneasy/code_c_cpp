#include <csignal>
#include <cstddef>
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <workflow/HttpMessage.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFGlobal.h>
#include <workflow/WFHttpServer.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>

using namespace std;
using namespace protocol;
using namespace std::placeholders;

WFFacilities::WaitGroup waitGroup(1);

void sig_handler(int)
{
    waitGroup.done();
}

void pread_callback(WFFileIOTask *task,HttpResponse *resp,string filename)
{
    FileIOArgs *args = task->get_args();
    close(args->fd);
    long bytes = task->get_retval();

    int state = task->get_state();
    if(state != WFT_STATE_SUCCESS)
    {
        cerr << WFGlobal::get_error_string(state, task->get_error());
        resp->set_status_code("500");
        resp->append_output_body("<html>500 Server Internal Error");
        return;
    }

    resp->add_header_pair("Content-Disposition",string("attachment; filename")+ filename);
    resp->append_output_body_nocopy(args->buf,bytes);
}

void process(WFHttpTask *httpTask)
{
    HttpRequest *req = httpTask->get_req();
    string uri = req->get_request_uri();
    auto pos = uri.find('?');
    string path = uri.substr(0,pos);
    if(path == "/")
    {
        path += "index.html";
    }
    path = "resources" + path;
    cout << "[path]" << path << endl;

    pos = path.find_last_of('/');
    string filename = path.substr(pos + 1);
    cout << "[filename]" << filename << endl;

    HttpResponse *resp = httpTask->get_resp();
    resp->add_header_pair("Server","Sogou C++ WorkFlow server");

    int fd = open(path.c_str(),O_RDONLY);
    if(fd == -1)
    {
        resp->set_status_code("404");
        resp->append_output_body("<html> 404 Not Found </html>");
        return;
    }

    struct stat statbuf;
    fstat(fd, &statbuf);
    size_t size = statbuf.st_size;
    cout << "size : " << size << endl;

    char *buf = (char*)malloc(size);
    assert(buf != NULL && "malloc failed");

    httpTask->set_callback([buf](WFHttpTask *task)
        {
            free(buf);
        });

    WFFileIOTask *preadTask = WFTaskFactory::create_pread_task
        (
            fd,buf,size,0,
            bind(pread_callback,_1,resp,filename)
        );

    series_of(httpTask)->push_back(preadTask);
}

int main(int argc,char *argv[])
{
    signal(SIGINT,sig_handler);
    WFHttpServer server(process);
    if(server.start(8888) == 0)
    {
        waitGroup.wait();
        server.stop();
    }else{
        cerr << "Error : Server start failed" << endl;
    }

    return 0;
}
