#include <iostream>
#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;
using josn =  nlohmann::json;

// 构建json对象
// 基本数据结构直接赋值
// 遇到歧义 用 array/object指定是数组还是对象
// push_back 向数组中追加元素、emplacement 向对象中添加元素
// STL容器可以转换成json的数组/对象，要看STL的具体容器

int main(int argc,char *argv[])
{
    // 1、构建基本数据结构
    // json 的基本数据结构 ： null , bool , 数字 ， 字符串
    josn j1 ;  // 无参构造方法
    cout << j1.dump() << endl;

    json j2 = false;
    cout << j2.dump() << endl;
    json j3 = 2.67;
    cout << j3.dump() << endl;
    json j4 = "Jo";
    cout << j4.dump() << endl;

    cout << "-------------" << endl;
    // 使用初始化列表构建json对象
    json j5 {"zyt","is","beautiful",666};
    cout << j5.dump(2) << endl;

    json j6 = {
        {"name","Jo"},
        {"age",30}
    };
    cout << j6.dump(2) << endl;

    cout << "-------解决歧义-------" << endl;
    // 解决歧义
    // 表示为空 null  ， " " 空字符串 ，[] 空数组  ， {}  空对象
    json j7; // null
    json j8 = ""; //空字符串
    json j9 = json::array();  //空数组
    cout << j9.dump(2) << endl;
    json j10 = json::object();  //空对象
    cout << j10.dump(2) << endl;

    cout << "--------嵌套数组---------" << endl;
    // 如何表示 [["currency","USD"],["value",42.99]]
    // 数组中嵌套数组
    //json d1 = {{"currency","USD"},{"value",42.99}};
    //cout << d1.dump(2) << endl;
    json d2 = json::array({{"currency","USD"},{"value",42.99}});
    cout << d2.dump(2) << endl;

    cout << "------动态构建------" << endl;
    // 动态构建Json
    json d4 ;         // null
    d4["pi"] = 3.14;  // null->object 一经转换不能改变
    d4["happy"] = true;
    d4["name"] = "Niels";
    d4["nothing"] = nullptr; // nullptr空值
    d4["answer"] ["everything"] = 42;
    d4["list"] = {1,2,3};  //数组  类似于vector
    d4["list"].push_back(4);
    d4["list"].push_back(5);
    d4["list"].push_back(6);

    d4["object"] = {{"currency","USD"},{"value",42.99}}; //对象 类似于map
    d4["object"].emplace("name","zyt");
    d4["object"].emplace("age","30");

    cout << d4.dump(2) << endl;


    return 0;
}
