#include <iostream>
#include <memory>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

// 前置声明，因为 TextQuery 的 query 函数需要返回这个类型
class QueryResult;

// ==================== 1. TextQuery 类定义 ====================
class TextQuery {
public:
    // 构造函数：接受文件流，一次性读完并建好索引
    TextQuery(ifstream &ifs);

    // 查询接口：传入单词，返回一个独立的结果对象
    QueryResult query(const string &inputWord) const;

private:
    // 核心数据：用智能指针共享的 vector，存放每一行原文
    shared_ptr<vector<string>> m_lines;

    // 核心索引：单词 -> 智能指针包裹的行号 set
    map<string, shared_ptr<set<int>>> m_wp;
};

// ==================== 2. QueryResult 类定义 ====================
class QueryResult {
    // 友元函数，允许重载的 << 运算符访问私有成员
    friend ostream &operator<<(ostream &os, const QueryResult &qr);

public:
    // 构造函数：只拷贝指针（快捷方式），不拷贝大数据
    QueryResult(string word, 
                shared_ptr<vector<string>> lines, 
                shared_ptr<set<int>> lineNo)
        : m_word(word), m_lines(lines), m_lineNo(lineNo) {}

private:
    string m_word;                      // 查询的单词
    shared_ptr<vector<string>> m_lines; // 指向 TextQuery 那份原文的指针
    shared_ptr<set<int>> m_lineNo;      // 指向该单词行号集合的指针
};

// ==================== 3. 成员函数实现 ====================

// TextQuery 构造函数：解析文本
TextQuery::TextQuery(ifstream &ifs) 
    : m_lines(make_shared<vector<string>>()) { // 用 make_shared 初始化原文数组
    
    string line;
    while (getline(ifs, line)) {
        m_lines->push_back(line);           // 存入当前行
        int line_idx = m_lines->size() - 1; // 记录当前行号（从0开始）

        istringstream iss(line);
        string word;
        while (iss >> word) {
            // lines_set 是 map 中智能指针的“引用（别名）”
            auto &lines_set = m_wp[word]; 
            if (!lines_set) {
                // 如果是新单词，为其分配一个 set 内存
                lines_set = make_shared<set<int>>(); 
            }
            lines_set->insert(line_idx);    // 自动去重、升序插入行号
        }
    }
}

// TextQuery 查询实现
QueryResult TextQuery::query(const string &inputWord) const {
    // 思考点：如果查不到，返回什么？
    // 我们用 static 创建一个全局唯一的空集合指针，避免每次查不到都新建内存
    static shared_ptr<set<int>> noData = make_shared<set<int>>();

    auto it = m_wp.find(inputWord);
    if (it == m_wp.end()) {
        return QueryResult(inputWord, m_lines, noData); // 没找到，传空集合指针
    } else {
        return QueryResult(inputWord, m_lines, it->second); // 找到了，传对应的行号指针
    }
}

// QueryResult 打印函数实现（重载 << 运算符）
ostream &operator<<(ostream &os, const QueryResult &qr) {
    // 打印总次数：集合的大小就是出现的行数
    os << qr.m_word << " occurs " << qr.m_lineNo->size() << " times." << endl;

    // 遍历共享的行号 set
    // 因为 qr.m_lineNo 是智能指针，我们需要用 * 解引用拿到真正的 set
    for (int lineNo : *qr.m_lineNo) {
        // 计算机行号从 0 开始，人类习惯从 1 开始，所以显示 lineNo + 1
        // 通过 m_lines 智能指针精准获取对应的行文本
        os << "    (line " << lineNo + 1 << ") " << qr.m_lines->at(lineNo) << endl;
    }
    return os;
}

// ==================== 4. 业务逻辑与主函数 ====================
void runQueries(ifstream &ifs) {
    // 正确的设计：在循环外部初始化数据库，只读一次文件！
    TextQuery tq(ifs); 

    while (true) {
        cout << "Enter word to look for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q") break;
        
        // 瞬间完成查询并打印
        cout << tq.query(s) << endl; 
    }
}

int main() {
    ifstream ifs("china_daily.txt");
    if (!ifs) {
        cerr << "Cannot open file!" << endl;
        return -1;
    }
    runQueries(ifs);
    return 0;
}