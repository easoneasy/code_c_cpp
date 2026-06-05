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

using namespace std;
using namespace protocol;

// 定义在整个任务流（Series）中共享的数据结构
struct SeriesContext {
    string url;      // 网页的url
    size_t size;     // 网页的大小
    bool success;    // 标志整个序列（流水线）是否最终成功
};

// ==========================================
// 2. MySQL 任务结束后的异步回调
// ==========================================
void mysql_callback(WFMySQLTask* mysqlTask)
{
    // 检查网络/传输层状态
    int state = mysqlTask->get_state();
    if (state != WFT_STATE_SUCCESS) {
        cerr << WFGlobal::get_error_string(state, mysqlTask->get_error()) << endl;
        return;
    }

    // 检查 MySQL 协议层报错（如：语法错误、表不存在）
    MySQLResponse* resp = mysqlTask->get_resp();
    if (resp->get_packet_type() == MYSQL_PACKET_ERROR) {
        cerr << resp->get_error_code() << " " << resp->get_error_msg() << endl;
        return;
    }

    // 从当前任务反查它所属的序列，进而拿到全局上下文
    SeriesWork* series = series_of(mysqlTask);
    SeriesContext* ctx = static_cast<SeriesContext*>(series->get_context());

    // 走到这里说明 HTTP 和 MySQL 都成功了
    ctx->success = true;

    // 使用游标解析刚刚 INSERT 成功后自动生成的自增 ID
    MySQLResultCursor cursor(resp);
    cout << "插入记录: id=" << cursor.get_insert_id() << endl;
}

// ==========================================
// 1. HTTP 请求完成后的异步回调
// ==========================================
void http_callback(WFHttpTask* httpTask)
{
    // 检查 HTTP 请求是否成功（如：404/DNS解析失败等）
    int state = httpTask->get_state();
    if (state != WFT_STATE_SUCCESS) {
        cerr << WFGlobal::get_error_string(state, httpTask->get_error()) << endl;
        return;
    }

    SeriesWork* series = series_of(httpTask);
    SeriesContext* ctx = static_cast<SeriesContext*>(series->get_context());

    // 提取 HTTP 响应体包头和大小
    HttpResponse* resp = httpTask->get_resp();
    const void* body;
    size_t size;
    resp->get_parsed_body(&body, &size);

    ctx->size = size; // 将获取到的网页大小更新到序列上下文中

    // 创建下一步的异步 MySQL 任务
    WFMySQLTask* mysqlTask = WFTaskFactory::create_mysql_task(
        "mysql://root:1234@localhost:3306/demo", 3, mysql_callback);

    // 【核心技巧】：从当前 HTTP 任务的 user_data 中安全取出 main 传进来的 URL
    string url = static_cast<char*>(httpTask->user_data);

    // 动态拼接 SQL（注意：生产环境直接拼接有 SQL 注入风险）
    string sql = "INSERT INTO tbl_webpage (url, size) VALUES ('"
        + url + "', " + std::to_string(size) + ")";
    cout << "[SQL] " << sql << endl;

    MySQLRequest* mysql_req = mysqlTask->get_req();
    mysql_req->set_query(sql);

    /* * ⚠️ 注意你的注释：如果这里调 mysqlTask->start()，
     * 框架会为 mysqlTask 单独开辟一条独立并行的新 Series 链，
     * 那样它就脱离了当前序列的控制，导致 main 里的 waitGroup 无法正确等待它。
     *
     * 正确做法：把新任务推入当前序列的末尾，让流水线继续向后延伸。
     */
    series->push_back(mysqlTask);
}

// ==========================================
// 主函数：负责组装流水线并启动
// ==========================================
int main(int argc, char* argv[])
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <URL>" << endl;
        return 1;
    }

    // 创建首个任务：HTTP 抓取
    WFHttpTask* httpTask = WFTaskFactory::create_http_task(argv[1], 3, 3, http_callback);

    // 绑定基础数据到 Task 级别的固有指针上
    httpTask->user_data = argv[1];

    // 配置 HTTP 请求头
    HttpRequest* req = httpTask->get_req();
    req->add_header_pair("Accept", "*/*");
    req->add_header_pair("User-Agent", "wget/1.14 (linux-gnu)");
    req->add_header_pair("Connection", "close"); // 爬完即断开 TCP

    // 防御性配置：限制防止大文件撑爆内存，设置30秒接收超时
    httpTask->get_resp()->set_size_limit(20 * 1024 * 1024);
    httpTask->set_receive_timeout(30 * 1000);

    // 计数器设为 1，用于阻塞主线程
    WFFacilities::WaitGroup waitGroup(1);

    // 创建SeriesWork（序列）。第二个参数是整个序列彻底结束（没有后续任务）时的总回调
    SeriesWork* series = Workflow::create_series_work(httpTask, [&waitGroup](const SeriesWork* series) {
        // 整个串行流结束，做最后的收尾盘点
        SeriesContext* ctx = static_cast<SeriesContext*>(series->get_context());
        if (ctx->success) {
            cout << "success!" << endl;
        } else {
            cout << "failed!" << endl;
        }

        delete ctx;          // 严格在流水线终点销毁 Context，防止内存泄漏
        waitGroup.done();    // 计数器减 1，唤醒主线程
    });

    // 动态开辟全局上下文并绑定到序列上
    SeriesContext* ctx = new SeriesContext { argv[1], 0, false };
    series->set_context(ctx);

    // 非阻塞启动序列，内部交由 Workflow 线程池调度
    series->start();

    // 主线程在此死等，直到异步回调流里发出 waitGroup.done() 信号
    waitGroup.wait();
    return 0;
}
