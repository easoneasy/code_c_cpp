#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

using namespace nlohmann;
using json = nlohmann::json;
using namespace std;


struct Student {
    int id;
    string name;
    int chinese;
    int math;
    int english;
    vector<string> hobbies;
    bool isGraduated;
};


// 4.1 把student对象转换成json
void test1()
{
    Student s =
        { 1001, "花生", 92, 95, 88, { "唱歌", "跳舞", "rap", "篮球" }, false };
    json data;
    data["id"] = s.id;
    data["name"] =s.name;
    data["score"]["chinese"] = s.chinese;
    data["score"]["math"] = s.math;
    data["score"]["english"] = s.english;
    // hobbies 数组
    // for(auto &e : s.hobbies)
    // {
    //     data["hobbies"] = e;
    // }
    // vector 可以自动转换成json数组
    data["hobbies"] = s.hobbies;
    data["isGraduated"] = s.isGraduated;
    cout << data.dump(2) << endl;
}

struct Book
{
    string title;
    string author;
    double price;
    string publisher;
    vector<string> tags;
};

// 将 json --> C++ 对象
void test2()
{
    // 定义json字符串
    const char *jsonstring = R"({
        "book": {
            "title": "JavaScript 高级程序设计",
            "author": "Nicholas C. Zakas",
            "price": 129.00,
            "publisher": "人民邮电出版社",
            "tags": ["前端", "JavaScript", "编程"]
        }
    })";
    // 解析json字符串
    json data = json::parse(jsonstring);

    // 创建book对象
    Book book;
    book.title = data["book"]["title"];
    book.author = data["book"]["author"];
    book.price = data["book"]["price"];
    book.publisher = data["book"]["publisher"];
    book.tags = data["book"]["tags"];

    // 打印书名、价格、标签
    cout << "title : " << book.title << "  "
        << ", price : " << book.price << "  "
        << ", tags : [";
    int ntags = book.tags.size();
    for(int i = 0 ; i < ntags ; ++i)
    {
        if(i != ntags-1)
        {
            cout << book.tags[i] << " , ";
        }else{
            cout << book.tags[i] << "]" << endl;
        }
    }

}

struct student
{
    string name;
    int age;
    string gender;
    vector<int> scores;
};

void test3()
{
    string json_str = R"([
    {
    "name": "赵一",
    "age": 18,
    "gender": "男",
    "scores": [85, 92, 78]
    },
    {
    "name": "钱二",
    "age": 19,
    "gender": "女",
    "scores": [96, 88, 94]
    },
    {
    "name": "孙三",
    "age": 18,
    "gender": "男",
    "scores": [76, 81, 69]
    }
    ])";

    json data = json::parse(json_str);
    vector<student> students;
    int max_score = 0;
    for(const auto &j : data)
    {
        student s;
        s.name = j["name"];
        s.age = j["age"];
        s.gender = j["gender"];
        s.scores = j["scores"].get<vector<int>>();
        // 将s对象放入students里
        students.push_back(s);

        int total_score = 0;
        for(int score : s.scores)
        {
            total_score += score;
        }
        if(total_score > max_score)
        {
            max_score = total_score;
        }
    }

    // 打印students的所有学生信息
    for(auto &e : students)
    {
        cout << "name : " << e.name << " " << "age : " << e.age << " "
        << " gender : " << e.gender << " socres : " ;
        for(auto score : e.scores)
        {
            cout << score << " ";
        }
        cout << endl;
    }
    cout << endl;

    // 计算每个学生的平均分
    for(auto &avg : students)
    {
        cout << avg.name << " average : ";
        int total_score = 0;
        for(int i = 0; i < avg.scores.size(); ++i)
        {
            total_score += avg.scores[i];
        }
        // 平均分：
        cout << total_score*1.0 / avg.scores.size() << endl;
    }

    // 找出所有18岁的学生，并打印出他们的名字
    cout << "18 years students : ";
    for(auto &e :students)
    {
        if(e.age == 18)
        {
            cout << e.name << " ";
        }
    }
    cout << endl;

    // 找出总分最高的学生，打印他们的名字
    cout << " max total_score students : " ;
    for(auto &s: students)
    {
        int total_score = 0;
        for(int i = 0;i<s.scores.size();++i)
        {
            total_score += s.scores[i];
        }
        if(total_score == max_score)
        {
            cout << s.name << endl;
        }

    }
    cout << endl;
}

int main(int argc,char *argv[])
{
    // test1();
    // test2();
    test3();

    return 0;
}
