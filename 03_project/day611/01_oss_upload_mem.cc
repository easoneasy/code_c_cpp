#include <alibabacloud/oss/client/ClientConfiguration.h>
#include <alibabacloud/oss/model/PutObjectRequest.h>
#include <iostream>
#include <alibabacloud/oss/OssClient.h>
#include <istream>
#include <memory>
#include <sstream>
using namespace std;
using namespace AlibabaCloud::OSS;


int main(int argc,char *argv[])
{
    // 1、初始化网络资源
    InitializeSdk();

    // 设置OSS账号信息，创建OssClient
    string endpoint = "oss-cn-wuhan-lr.aliyuncs.com";
    string accessKeyId = "LTAI5t8kNWH4c5FaSFExmMfg";
    string accessKeySecret = "8b0dMuaCmvm7DqzhynI0m5PB0ND6r2";
    string region = "cn-wuhan";
    //
    ClientConfiguration conf;
    OssClient client(endpoint,accessKeyId,accessKeySecret,conf);
    client.SetRegion(region);

    // 上传文件
    string bucketName = "jo-bucket";
    string objectName = "dir/demo1.txt";
    string content = "Hello AlibabaCloud OSS";
    shared_ptr<iostream> stream = make_shared<stringstream>(move(content));
    PutObjectRequest request(bucketName,objectName,stream);
    auto outcome = client.PutObject(request);

    // 错误处理
    if(!outcome.isSuccess())
    {
        cout << "PutObject FAILED"
        << ", code : " << outcome.error().Code()
        << ", message : " << outcome.error().Message()
        << ", requestId : " << outcome.error().RequestId() << endl;
        exit(1);
    }

    // 释放网络资源
    ShutdownSdk();

    return 0;
}
