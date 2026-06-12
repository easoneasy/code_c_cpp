#include <SimpleAmqpClient/BasicMessage.h>
#include <SimpleAmqpClient/Channel.h>
#include <iostream>
#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <string>
using namespace std;
using namespace AmqpClient;

int main(int argc,char *argv[])
{
    // 创建Channel
    string host = "127.0.0.1";
    int port = 5672;
    string username = "guest";
    string password = "guest";
    string vhost = "/";
    Channel::ptr_t channel = Channel::Create(host,port,username,password,vhost);

    // 构建消息
    BasicMessage::ptr_t message = BasicMessage::Create("Hello RabbitMQ");

    // 发送消息
    // 交换机
    string exchange = "oss.direct";
    // 消息的routineKey
    string routingKey = "oss";
    // 发布消息
    channel->BasicPublish(exchange, routingKey, message);

    return 0;
}
