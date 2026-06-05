#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
struct Record
{
    Record(const string &word,int frequency)
    :m_word(word)
    ,m_frequency(frequency)
    {}
	string m_word;
	int m_frequency;
};
bool operator<(const Record &lhs,const Record &rhs)
{
    return lhs.m_word < rhs.m_word;
}
class Dictionary
{
public:
	//构造函数
    Dictionary(int capacity)
    {
        m_dict.reserve(capacity);
    }
    void dealWord(string &data)
    {
        auto it = data.begin();
        while(it != data.end())
        {
            if(isalpha(*it))
            {
                ++it;
            }else{
                it = data.erase(it);
            }
        }
    }
    void insert(const string &data)
    {
        //空字符串跳过
        if(data.empty())
        {
            return;
        }
        bool found = false;
        for(size_t i = 0;i <m_dict.size();++i)
        {
            //判断此单词是否存在于vector中
            if(m_dict[i].m_word == data)
            {
                //存在就将词频+1
                m_dict[i].m_frequency++;
                found = true;
                break;
            }
        }
        //不存在就创建新的记录
        if(!found)
        {
            m_dict.push_back(Record(data,1));
        }

    }
    void read(const std::string &filename)
    {
        ifstream ifs(filename);
        if(!ifs)
        {
            cout << "ifstream open failed" << endl;
            return;
        }
        string line;
        //每次读取一整行
        while(getline(ifs,line))
        {
            //从字符串中读取数据
            istringstream iss(line);
            string word;
            //将字符串写入到单词中
            while(iss >> word)
            {
                dealWord(word); //清洗单词
                insert(word); //存入vector
            }
        }
        //将vector中的数据排序
        sort(m_dict.begin(),m_dict.end());
        ifs.close();
    }
    //将vector中的数据存入文件内
    void store(const std::string &filename)
    {
        //输入ofs
        ofstream ofs(filename);
        if(!ofs)
        {
            cout << "ofstream open failed" << endl;
            return;
        }
        for(auto &e : m_dict)
        {
            ofs << e.m_word << " " <<e.m_frequency << endl;
        }
        ofs.close();
    }
private:
    vector<Record> m_dict;
};
void test1()
{
    Dictionary dic(10000);
    dic.read("The_Holy_Bible.txt");
    dic.store("data.txt");
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

