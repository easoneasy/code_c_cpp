#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <memory>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

class TextQuery
{
public:
    void readFile(const string filename)
    {
        //初始化动态数组，存放文件的每一行
        //使用make_shared创建一个vector<string>让智能指针指向它
        _lines = make_shared<vector<string>>();
        //打开指定文件
        ifstream ifs{filename};
        if(!ifs)
        {
            cout << "open file faield" << endl;
        }
        //逐行读取文件的内容
        string line;
        while(getline(ifs,line))
        {
            //放入动态数组中
            _lines->push_back(line);
            //记录行号（从0开始，vector当前的长度-1，就是索引)
            int line_index = _lines->size()-1;
            //使用字符串流，将一行文本拆成单词
            istringstream iss{line};
            string word;
            while(iss >> word)
            {
                //在map索引表中查找或创建该单词的行号
                auto &line_set = _wordNumbers[word];
                //如果指针为空，说明是第一次遇到这个单词，为它分配set
                if(line_set == nullptr)
                {
                    line_set = make_shared<set<int>>();
                }
                //将当前行号插入到单词对应的set集合中
                line_set->insert(line_index);
            }
        }
    }
    
private:
    shared_ptr<vector<string>> _lines;
    map<string,shared_ptr<set<int>>> _wordNumbers;
};

void test1()
{

}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

