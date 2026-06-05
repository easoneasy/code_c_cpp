#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

//构建转换映射表
unordered_map<string,string> buildMap(ifstream &map_file)
{
    unordered_map<string,string> trans_map;
    string key;
    string value;
    //将读取到的第一个单词存入key，将这一行剩余的所有内容（包括空格）存入value
    while(map_file >> key && getline(map_file,value))
    {
        //确保value不是空的
        if(value.size() > 1)
        {
            //使用substr抹掉空格
            trans_map[key] = value.substr(1);
        }
    }
    return trans_map;
}

//转换单词的核心函数
const string &transform(const string &s,const unordered_map<string,string> &m)
{
    //在unordered_map中查找单词
    auto it = m.find(s);
    if(it != m.end())
    {
        //找到了就返回容器的value
        return it->second;
    }else{
        //没找到就原样返回
        return s;
    }
}

//文本转换
void wordTransform(ifstream &map_file , ifstream &input_file)
{
    //调用转换映射表
    auto trans_map = buildMap(map_file);
    //按行转换文件
    string line;
    while(getline(input_file,line))
    {
        //用字符串流将一行拆分成单个的单词
        istringstream stream{line};
        string word;
        //控制空格输出的标记
        bool isFirstWord = true;
        while(stream >> word)
        {
            if(!isFirstWord)
            {
                //单词之间打印空格
                cout << " " ;
            }
            isFirstWord = false;
            cout << transform(word,trans_map);
        }
        cout << endl;
    }
}

void test1()
{
    //打开规则文件和待转换文件
    ifstream map_file("map.txt");
    ifstream file_to_trans("file.txt");
    if(!map_file)
    {
        cout << "无法打开map.txt" << endl;
        return;
    }
    if(!file_to_trans)
    {
        cout << "无法打开file.txt" <<endl;
        return ;
    }
    wordTransform(map_file,file_to_trans);
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

