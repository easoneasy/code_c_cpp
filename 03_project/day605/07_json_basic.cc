#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;
using josn =  nlohmann::json;
void test1()
{
    ifstream f{"example.json"};
    json j1 = json::parse(f);   // 反序列化操作
    cout << j1.dump() << endl;  // 序列化操作

    // 2、解析字符串 (裸字符串)
    json j2 = json::parse(R"({
        "pi" : 3.14,
        "happy" : true;
        })");
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}
