#include <my_header.h>
#include "queue.h"
#include"pthread_pool.h"
#include"work.h"
#include"socket.h"
#include"epoll.h"

int main(int argc,char *argv[]){
    //初始化线程池
    threadpool_t pool;
    init_pthread_pool(4,&pool);
    //初始化socket
    int lisfd;
    init_listen_socket(&lisfd,"192.168.254.128","12345");
    //创建epoll
    int epfd = epoll_create(1);
    //将lisfd放在红黑树上监听
    add_epoll_ctl(epfd,lisfd);

    int conn_fd=0;
    while(1){
        struct epoll_event lst[100];
        int nready=epoll_wait(epfd,lst,100,-1);
        printf("%d is ready.\n",nready);
        for(int i=0;i<nready;i++){
            int fd = lst[i].data.fd;
            printf("fd is lisfd\n");
            if(fd==lisfd){
                printf("accept");
                conn_fd=accept(lisfd,NULL,NULL);
                //给队列加锁
                printf("pthread_mutex_lock\n");
                pthread_mutex_lock(&pool.lock);
                //把文件描述符放入队列中
                printf("insert_queue\n");
                insert_queue(&pool.queue,conn_fd);
                //唤醒锁
                printf("pthread_cond_signal\n");
                pthread_cond_signal(&pool.cond);
                //给队列解锁
                printf("pthread_mutex_unlock\n");
                pthread_mutex_unlock(&pool.lock);
            }

        }
    }



    return 0;
}

