#include <my_header.h>
#include"queue.h"
#include"pthread_pool.h"
#include"work.h"
#include"send_file.h"
#include"socket.h"
#include"epoll.h"
int pipefd[2]={0};

void signal_fun(int num){
    //父进程通过管道给子进程发送消息
    printf("num = %d\n",num);
    write(pipefd[1],"1",1);
}

int main(int argc,char *argv[]){
    //创建匿名管道
    pipe(pipefd);
    //创建子进程
    int fork_ret = fork();
    if(fork_ret!=0){
        //父线程
        //信号处理函数
        signal(2,signal_fun);
        wait(NULL);
        return 0;

    }
    //子进程，脱离当前会话，成为新的进程组组长
    setpgid(0,0);

    pthread_pool pool;
    //创建线程池,创建4个子线程
    init_thread_pool(&pool,4);

    //初始化socket
    int lisfd=0;
    init_socket(&lisfd,"192.168.254.128","12345");
    
    int epfd = epoll_create(1);
    //将lisfd和pipefd放入红黑树上
    add_epoll_ctl(epfd,lisfd);
    add_epoll_ctl(epfd,pipefd[0]);

    while(1){
        struct epoll_event lst[100];
        int nready=epoll_wait(epfd,lst,100,-1);
        for(int i=0;i<nready;i++){
            int fd=lst[i].data.fd;
            if(fd==lisfd){
                int confd=accept(fd,NULL,NULL);
                printf("----------accept---------------\n");
                //把监听到的文件描述符放入队列中
                pthread_mutex_lock(&pool.lock);
                insert_queue(confd,&pool.queue);
                //唤醒锁
                pthread_cond_signal(&pool.cond);
                pthread_mutex_unlock(&pool.lock);
            }
            //判断管道是否有消息发过来
            if(fd==pipefd[0]){
                char buff[5]={0};
                printf("recv msg from pipe\n");
                read(fd,buff,sizeof(buff));
                //收到消息之后杀死子线程
                for(int j=0;j<pool.pthread_num;j++){
                    printf("pthread cancel\n");
                    pthread_cancel(pool.pthread_id[j]);
                    printf("pthread cancel over\n");
                }
                //主线程等待子线程
                for(int j=0;j<pool.pthread_num;j++){
                    printf("pthread join\n");
                    pthread_join(pool.pthread_id[j],NULL);
                    printf("pthread join over\n");
                }
                //等待所有子线程退出完毕，主线程退出
                pthread_exit((void *)NULL);
                continue;
            }
        }
    }



    return 0;
}

