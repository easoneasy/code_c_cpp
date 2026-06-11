#include <alibabacloud/oss/client/ClientConfiguration.h>
#include <alibabacloud/oss/model/PutObjectRequest.h>
#include <iostream>
#include <alibabacloud/oss/OssClient.h>
#include <istream>
#include <memory>
#include <sstream>
using namespace std;
using namespace AlibabaCloud::OSS;
// 静态单例
class OSSManager
{
public:
    static OSSManager &getInstance()
	{
		static OSSManager instance;
        return instance;
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
    ~OSSManager()
	{
		// 释放客户端
		_client.reset();
		// 释放网络资源
		ShutdownSdk();
	}

private:
	// 保存一个OssClient对象
	// 保证这个对象在OSSManager整个生命周期内一直存在
    unique_ptr<OssClient> _client;
	string _bucketName;
};

int main(int argc,char *argv[])
{
    OSSManager::getInstance().upload("text","hello");

    return 0;
}
