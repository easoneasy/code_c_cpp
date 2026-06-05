#include <my_header.h>

typedef struct conn
{
    int fd; //文件描述符
    int alive; //连接是不是存活的，活就是1，死就是0
}conn_t;

int main(int argc, char *argv[])
{
    char *ip = "192.168.254.128";
    char *port = "12345";

    //创建用于监听的文件描述符
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(listen_fd, -1, "socket");

    //端口复用
    int opt = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));

    //绑定服务器的ip与端口号
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    //在对结构体遍历addr进行填充
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
    addr.sin_addr.s_addr = inet_addr(ip);

    int ret = bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr));
    ERROR_CHECK(ret, -1, "bind");

    //监听客户端
    ret = listen(listen_fd, 10);
    ERROR_CHECK(ret, -1, "listen");

    //存放群聊中客户端的个数的数组
    conn_t con_arr[100] = {0};
    int size = 0;

    fd_set set;
    FD_ZERO(&set);
    FD_SET(listen_fd, &set);

    while(1)
    {
        fd_set tmp;//临时位图
        tmp = set;

        int nready = select(100, &tmp, NULL, NULL, NULL);
        ERROR_CHECK(ret, -1, "select");
        printf("nready: %d\n", nready);

        if(FD_ISSET(listen_fd, &tmp))
        {
            int conn_fd = accept(listen_fd, NULL, NULL);
            ERROR_CHECK(conn_fd, -1, "accept");

            con_arr[size].fd = conn_fd;
            con_arr[size].alive = 1;
            ++size;

            //需要将conn_fd放在监听集合中进行监听
            FD_SET(conn_fd, &set);
        }

        //需要遍历size
        for(int idx = 0; idx < size; ++idx)
        {
            //从数组中取出其中的值
            int fd = con_arr[idx].fd;

            //表明有数据从老的连接上发过来了
            if(FD_ISSET(fd, &tmp))
            {
                char buf[50] = {0};
                //recv的返回结果是实际接收的数据的个数
                int cnt = recv(fd, buf, sizeof(buf), 0);
                if(0 == cnt)
                {
                    printf("客户端fd = %d断开了\n", fd);
                    con_arr[idx].fd = 0;
                    con_arr[idx].alive = 0;

                    //客户端断开后就不需要进行监听了，所以需要从set中
                    //清除
                    FD_CLR(fd, &set);
                    close(fd);

                    continue;
                }

                //转发给其他的客户端
                //这个代码还没有开始写-------*****
                for(int pos = 0; pos < size; ++pos)
                {
                    //转发给的其他客户端如果是断开的，就不发
                    //pos == idx说明是自己
                    if(0 == con_arr[pos].alive || pos == idx)
                    {
                        continue;
                    }
                    send(con_arr[pos].fd, buf, sizeof(buf), 0);
                }
            }
        }
    }

    close(listen_fd);

    return 0;
}


