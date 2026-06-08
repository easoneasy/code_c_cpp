#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

using namespace std;
using namespace nlohmann;
using josn =  nlohmann::json;

struct Student {
    int id;
    string name;
    int chinese;
    int math;
    int english;
    vector<string> hobbies;
    bool isGraduated;
};

void test1()
{
    Student s = { 1001, "花生", 92, 95, 88, { "唱歌", "跳舞", "rap", "篮球" }, false };

    json data;  // json对象
    data["id"] = s.id;
    data["name"] = s.name;
    data["scores"]["chinese"] = s.chinese;
    data["scores"]["math"] = s.math;
    data["scores"]["english"] = s.english;
    data["hobbies"] = s.hobbies;
    data["isGraduated"] = s.isGraduated;
    cout << data.dump(2) << endl;
}

// 将json对象解析为c++对象
// 获取书名、价格、标签
const char* str = R"({
    "book": {
        "title": "JavaScript 高级程序设计",
        "author": "Nicholas C. Zakas",
        "price": 129.00,
        "publisher": "人民邮电出版社",
        "tags": ["前端", "JavaScript", "编程"]
    }
    })";

struct Book
{
    string title;
    string author;
    double price;
    string publisher;
    vector<string> tags;
};

void test2()
{
    // 1、将json字符串反序列化 parse
    // 获取json对象
    json data = json::parse(str);
    cout << data.dump() << endl;

    Book book;
    book.title = data["book"]["title"];
    book.author = data["book"]["author"];
    book.price = data["book"]["price"];
    book.publisher = data["book"]["publisher"];
    // book.tags = data["tags"];
    for(const auto &tag :data["book"]["tags"])
    {
        book.tags.push_back(tag);
    }

    cout << "title : " << book.title << endl;
    cout << "price : " << book.price << endl;
    cout << "tags : " ;
    for(const auto &tag : book.tags)
    {
        cout << tag << " " ;
    }
    cout << endl;
}


int main(int argc,char *argv[])
{
    // test1();
    test2();

    return 0;
}
