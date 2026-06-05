#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>

using namespace std;
class TextQuery
{
public:
    // 构造函数
    TextQuery()
    {
        m_lines.reserve(1000);
    }
    // 读取并处理文件
    void readFile(const string &filename)
    {
        ifstream ifs{filename};
        if (!ifs)
        {
            cout << "open file failed" << endl;
            return;
        }
        string line;
        int lineNumber = 1;
        while (getline(ifs, line))
        {
            // 将一行原始数据存储到vector中
            m_lines.push_back(line);
            // 清洗一行数据
            dealLine(line);
            // 读取单词
            istringstream iss(line);
            string word;
            while (iss >> word)
            {
                // 统计词频
                ++m_dict[word];
                // 记录行号
                m_wordNumbers[word].insert(lineNumber);
            }
            ++lineNumber;
        }
        ifs.close();
    }
    // 查询单词输出结果
    void query(const string &word)
    {
        // 统一转换，将大写改成小写
        string cleanWord = word;
        for (auto &ch : cleanWord)
        {
            ch = tolower(ch);
        }
        // 检查单词是否存在，使用find查找,避免[]自动插入新元素
        auto ditIt = m_dict.find(cleanWord);
        // 如果找不着或词频为0，直接返回
        if (ditIt == m_dict.end() || ditIt->second == 0)
        {
            cout << word << " occurs 0 times" << endl;
            return;
        }
        // 获取词频和行号的集合
        int count = ditIt->second;
        cout << word << " occurs " << count << "  times " << endl;

        // 读取行
        const set<int> &lineNumbers = m_wordNumbers[cleanWord];
        // 遍历行号，输出原始文本
        for (int num : lineNumbers)
        {
            cout << "(line " << num << ")" << m_lines[num - 1] << endl;
        }
    }

private:
    // 清洗单词
    void dealLine(string &line)
    {
        // 在原始行中处理单词
        // 如果不是单词就替换成空格
        // 如果是大写就改成小写
        for (auto &ch : line)
        {
            if (!isalpha(ch))
            {
                ch = ' ';
            }
            else if (isupper(ch))
            {
                ch = tolower(ch);
            }
        }
    }
    // 存储原始文本
    vector<string> m_lines;
    // 存储单词所在行号
    map<string, set<int>> m_wordNumbers;
    // 存储单词出现的次数
    map<string, int> m_dict;
};
void test1()
{
    string queryWord("the");

    TextQuery tq;
    tq.readFile("china_daily.txt");
    tq.query(queryWord);
}

int main(int argc, char *argv[])
{

    test1();

    return 0;
}
