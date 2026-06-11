#pragma once
#include <alibabacloud/oss/model/GetObjectRequest.h>
#include <wfrest/HttpServer.h>
#include <workflow/WFFacilities.h>
#include <alibabacloud/oss/client/ClientConfiguration.h>
#include <alibabacloud/oss/model/PutObjectRequest.h>
#include <iostream>
#include <alibabacloud/oss/OssClient.h>
#include <istream>
#include <memory>
#include <sstream>

using namespace std;
using namespace std::placeholders;
using namespace wfrest;
using namespace protocol;
using namespace AlibabaCloud::OSS;
// 面向对象：将专业的事情交给专业的“人”去做

// 设计原则：武学心法
// 设计模式：招数

// 设计原则：组合优于继承
//     组合：有选择的复用代码
//     继承：会复用基类的所有代码，代码复用的技术！

// 装饰器模式（Wrapper）: 组合
//     保持接口一致，可以降低用户的学习成本
class CloudDiskServer {
    public:
        CloudDiskServer() { }

        // 注册路由
        void register_routes();

        // 包装了一层: 要保证包装后的接口与原来的接口一致！
        int start(unsigned short port)
        {
            return server_.start(port);
        }

        void stop() { server_.stop(); }

        void list_routes() { server_.list_routes(); }

    private:
        // 注册路由
        void register_www_module();
        void register_auth_module();
        void register_user_module();
        void register_file_module();

    private:
        // 名字中最好不要带具体的实现细节
        // 方便以后修改具体的实现
        wfrest::HttpServer server_; // 组合
};


class OSSManager
{
    public:
        static OSSManager &getInstance()
        {
            static OSSManager instance;
            return instance;
        }
        // 析构函数
        ~OSSManager()
        {
            // 释放客户端
            _client.reset();
            // 释放网络资源
            ShutdownSdk();
        }
        bool upload(const string &objectName,const string &data)
        {

            auto stream = make_shared<stringstream>((data));
            PutObjectRequest request(_bucketName,objectName,stream);
            auto outcome = _client->PutObject(request);
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
        bool download(const string &objectName,string &data)
        {
            // 获取目标文件
            GetObjectRequest request(_bucketName,objectName);
            // 发送下载请求
            auto outcome = _client->GetObject(request);
            // 检查是否成功
            if(!outcome.isSuccess())
            {
                // 失败
                cout << "GetObject Failed"
                << ",code: " << outcome.error().Code()
                << ",message: " << outcome.error().Message()
                << endl;
                return false;
            }
            // 成功
            // OSS返回文件流 stream
            // 需要string类型 stringstream --> string
            stringstream ss;
            ss << outcome.result().Content()->rdbuf();
            data = ss.str();
            return true;
        }

    private:
        // 删除复制控制的函数
        OSSManager(const OSSManager &) = delete;
        OSSManager &operator=(const OSSManager &) = delete;

        // 构造函数私有
        OSSManager()
        :_bucketName("jo-bucket")
        {
            // 初始化网络资源
            InitializeSdk();
            // 设置OSS账号信息，创建OssClient
            string endpoint = "oss-cn-wuhan-lr.aliyuncs.com";
            string accessKeyId = "LTAI5t8kNWH4c5FaSFExmMfg";
            string accessKeySecret = "8b0dMuaCmvm7DqzhynI0m5PB0ND6r2";
            string region = "cn-wuhan";

            // 客户端配置对象
            ClientConfiguration conf;
            // 创建OSS客户端
            _client = make_unique<OssClient>(endpoint,accessKeyId,accessKeySecret,conf);

        }


    private:
        // 保存一个OssClient对象
        // 保证这个对象在OSSManager整个生命周期内一直存在
        unique_ptr<OssClient> _client;
        string _bucketName;
};
