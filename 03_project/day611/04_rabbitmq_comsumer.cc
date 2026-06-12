#include <SimpleAmqpClient/Channel.h>
#include <SimpleAmqpClient/Envelope.h>
#include <iostream>

using namespace std;
using namespace AmqpClient;

int main(int argc,char *argv[])
{
    // 以URI的方式创建Channel  % 转义字符，2f是/
    string uri = "amqp://guest:guest@localhost:5672/%2f";
    Channel::ptr_t channel = Channel::CreateFromUri(uri);

    // 获取消息
    // // 方式1 ： 拉取模式 --消费者主动从队列中拉取消息（非阻塞
    // const string &q = "oss.queue";
    // // 如果队列中有消息，将消息放入evelop中，并返回true
    // // 如果队列中没有消息，BasicGet会立刻返回false
    // Envelope::ptr_t envelope;
    // channel->BasicGet(envelope, q);
    // // 打印消息
    // if(envelope && envelope->Message())
    // {
    //     cout << envelope->Message()->Body() << endl;
    // }

    // 方式2 ： 推送模式 -- 等待RabbitMQ推送消息（阻塞
    const string &q = "oss.queue";
    // 订阅队列
    // channel->BasicConsume(q);
    // // 阻塞： 等待RabbitMQ推送消息
    // Envelope::ptr_t envelope = channel->BasicConsumeMessage();
    //
    string consumer_tag = channel->BasicConsume(q);
    Envelope::ptr_t envelope;
    channel->BasicConsumeMessage(consumer_tag,envelope);

    // 打印消息
    if(envelope && envelope->Message())
    {
        cout << envelope->Message()->Body() << endl;
    }

    return 0;
}
