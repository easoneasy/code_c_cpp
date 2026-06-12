#include <SimpleAmqpClient/BasicMessage.h>
#include <SimpleAmqpClient/Channel.h>
#include <SimpleAmqpClient/Envelope.h>
#include <fcntl.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <alibabacloud/oss/model/GetObjectRequest.h>
#include <alibabacloud/oss/client/ClientConfiguration.h>
#include <alibabacloud/oss/model/PutObjectRequest.h>
#include <alibabacloud/oss/OssClient.h>
using namespace std;
using namespace AmqpClient;
using json = nlohmann::json;
using namespace AlibabaCloud::OSS;

class OSSManager
{
    public:
        static OSSManager &getInstance();
        // 析构函数
        ~OSSManager();
		// 上传
        bool upload(const string &objectName,const string &data);
		// 下载
        bool download(const string &objectName,string &data);

    private:
        // 删除复制控制的函数
        OSSManager(const OSSManager &) = delete;
        OSSManager &operator=(const OSSManager &) = delete;

        // 构造函数私有
        OSSManager();

    private:
        // 保存一个OssClient对象
        // 保证这个对象在OSSManager整个生命周期内一直存在
        unique_ptr<OssClient> _client;
        string _bucketName;
};

// 创建单例对象
OSSManager &OSSManager::getInstance()
{
    static OSSManager instance;
    return instance;
}

// 构造函数
OSSManager::OSSManager()
{
    // 读取配置文件,获取OSS账号信息
    // ifstream ifs{"config.json"};
    // if(!ifs.is_open())
    // {
    //     cerr << "Error : connot open config.json" << endl;
    //     abort();
    // }
    // json config = json::parse(ifs);
    // ifs.close();
    string endpoint = "xxx";
    string accessKeyId = "xxxx";
    string accessKeySecret = "xxxx";
    _bucketName = "xxxx";
    string region = "cn-wuhan";

    // 初始化网络资源
    InitializeSdk();

    // 客户端配置对象
    ClientConfiguration conf;
    // 创建OSS客户端
    _client = make_unique<OssClient>(endpoint,accessKeyId,accessKeySecret,conf);
}

// 析构函数
OSSManager::~OSSManager()
{
    // 释放客户端
    _client.reset();
    // 释放网络资源
    ShutdownSdk();
}

// 上传
bool OSSManager::upload(const string &objectName,const string &path)
{
    // auto stream = make_shared<stringstream>((data));
    // PutObjectRequest request(_bucketName,objectName,stream);
    // auto outcome = _client->PutObject(request);

    // 从本地上传
    auto outcome = _client->PutObject(_bucketName,objectName,path);

    // 错误处理
    if(!outcome.isSuccess())
    {
        cout << "PutObject FAILED"
        << ", code : " << outcome.error().Code()
        << ", message : " << outcome.error().Message()
        << ", requestId : " << outcome.error().RequestId() << endl;
        return false;
    }
    return true;
}

// 单例
class RabbitMQ
{
public:
    // 创建单例对象
    static RabbitMQ &getInstance()
    {
        static RabbitMQ instance;
        return instance;
    }
    // 生产者函数
    bool RabbitProducer(const string &fileName,const string localPath)
    {
        json data;
        data["filename"] = fileName;
        data["path"] = localPath;
        // 构建消息
        BasicMessage::ptr_t message = BasicMessage::Create(data.dump());
        // 发送消息
        string exchange = "oss.direct";
        string routingKey = "oss";
        // 发布消息
        _channel->BasicPublish(exchange, routingKey, message);
        return true;
    }
    // 消费者函数
    // typedef boost::shared_ptr<Envelope> ptr_t;
    //ptr_t 是类型别名（指针的类型别名）
    Envelope::ptr_t RabbitConsumer()
    {
        // 检查是否有消费者对象
        if(_consumerTag.empty())
        {
            return nullptr;
        }
        // 订阅队列
        Envelope::ptr_t envelope;
        // 把消息放入envelope
        _channel->BasicConsumeMessage(_consumerTag,envelope);
        // 把收到的消息返回给调用者
        return envelope;
    }

    // 创建消费者函数
    void startConsumer()
    {
        _consumerTag = _channel->BasicConsume("oss.queue","",false,false,false,1);
    }

    // ACK接口
    void Ack(Envelope::ptr_t env)
    {
        _channel->BasicAck(env);
    }

private:
    // 构造函数
    RabbitMQ()
    :_uri("amqp://guest:guest@localhost:5672/%2f")
    {
        // 创建channel
        _channel = Channel::CreateFromUri(_uri);
    }
    // 析构函数
    ~RabbitMQ() = default;
    // 删除复制控制函数
    RabbitMQ(const RabbitMQ&) = delete;
    RabbitMQ &operator=(const RabbitMQ&) = delete;

private:
    string _uri;
    Channel::ptr_t _channel;
    string _consumerTag;
};


void OssWorker()
{
    RabbitMQ::getInstance().startConsumer();
    while (1)
    {
        // 获取的是消息，env格式
        auto env = RabbitMQ::getInstance().RabbitConsumer();
        auto data = json::parse(env->Message()->Body());

        string filename = data["filename"];
        string path = data["path"];
        bool ret = OSSManager::getInstance().upload(filename,path);
        if(ret)
        {
            RabbitMQ::getInstance().Ack(env);
            break;
        }
    }
}

int main(int argc,char *argv[])
{
    RabbitMQ::getInstance().RabbitProducer("a.txt", "./a.txt");
    // 主线程 + 子线程
    // 主线程发送消息，子线程接收消息
    // 消息是json数据（文件hash、path）

    OssWorker();

    return 0;
}
