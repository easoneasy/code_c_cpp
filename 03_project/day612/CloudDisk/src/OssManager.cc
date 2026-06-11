#include "../include/OssManager.h"
#include <sstream>
#include <alibabacloud/oss/model/GetObjectRequest.h>
#include <alibabacloud/oss/client/ClientConfiguration.h>
#include <alibabacloud/oss/model/PutObjectRequest.h>
#include <alibabacloud/oss/OssClient.h>

using namespace std;
using namespace AlibabaCloud::OSS;

// 创建单例对象
OSSManager &OSSManager::getInstance()
{
    static OSSManager instance;
    return instance;
}

// 构造函数
OSSManager::OSSManager()
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

// 析构函数
OSSManager::~OSSManager()
{
    // 释放客户端
    _client.reset();
    // 释放网络资源
    ShutdownSdk();
}

// 上传
bool OSSManager::upload(const string &objectName,const string &data)
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

// 下载
bool OSSManager::download(const string &objectName,string &data)
{
    // 获取目标文件
    GetObjectRequest request(_bucketName,objectName);
    // 发送下载请求
    auto outcome = _client->GetObject(request);
    // 检查是否成功
    if(!outcome.isSuccess())
    {
        // 失败
        cout << "GetObject FAILED"
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
