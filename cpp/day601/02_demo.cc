#include <iostream>
#include <workflow/WFHttpServer.h>
#include <workflow/WFTaskFactory.h>
using namespace std;
using namespace protocol;

int main(int argc,char *argv[])
{
    //创建http服务器
    WFHttpServer server([](WFHttpTask* task){
        //获取HTTP任务的响应
        HttpResponse* resp=task->get_resp();
        //向响应报文中追加数据
        resp->append_output_body(R"(
            <!DOCTYPE html>
            <html lang="en">
            <head>
                <meta charset="UTF-8">
                <title>Minimalist Photo Gallery</title>
            </head>
            <body>

                <!-- Main Header -->
                <h1>My Photo Gallery</h1>
                <p>Click on any image to view it in full size.</p >
                <hr> <!-- Horizontal Rule Divider -->

                <!-- Photo 1 -->
                <h3>1. Mountain Morning</h3>
                <a href=" " target="_blank">
                    < img src="https://images.unsplash.com/photo-1506744038136-46273834b3fb?w=300" alt="Mountains" width="300">
                </a >
                <p>A misty morning in the early autumn mountains.</p >

                <br><br> <!-- Line Breaks for spacing -->

                <!-- Photo 2 -->
                <h3>2. Forest Sunlight</h3>
                <a href="https://images.unsplash.com/photo-1470071459604-3b5ec3a7fe05" target="_blank">
                    < img src="https://images.unsplash.com/photo-1470071459604-3b5ec3a7fe05?w=300" alt="Forest" width="300">
                </a >
                <p>The first rays of sun piercing through the deep woods.</p >

                <br><br>

                <!-- Photo 3 -->
                <h3>3. Peaceful River</h3>
                <a href="https://images.unsplash.com/photo-1447752875215-b2761acb3c5d" target="_blank">
                    < img src="https://images.unsplash.com/photo-1447752875215-b2761acb3c5d?w=300" alt="River" width="300">
                </a >
                <p>Spending a quiet afternoon listening to the flowing water.</p >

                <hr>
                <footer>
                    <p>&copy; 2026 Pure HTML Gallery</p >
                </footer>

            </body>
            </html>
        )");
    });

    //启动服务器
    if(server.start(8848)==0){
        getchar();
        server.stop();
    }else{
        cerr<<"ERROR:Server Start Failed."<<endl;
        exit(1);
    }

    return 0;
}