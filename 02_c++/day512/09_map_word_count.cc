#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

class Dictionary
{
public:
    void read(const string &filename)
    {
        ifstream ifs(filename);
        if(!ifs)
        {
            cout << "open file failed"<< endl;
            return;
        }
        string line;
        while(getline(ifs,line))
        {
            istringstream iss(line);
            string word;
            while(iss >> word)
            {
                dealWord(word);
                if(!word.empty())
                {
                    ++m_dict[word];
                }
            }
        }
        ifs.close();
    }
    void store(const string &filename)
    {
        ofstream ofs(filename);
        if(!ofs)
        {
            cout << "file not exisit" << endl;
            return;
        }
        //向文件输出统计的结果
        for(auto &e : m_dict)
        {
            ofs << e.first << " " << e.second << endl;
        }
        ofs.close();
    }
private:
    void dealWord(string &word)
    {
        auto it = word.begin();
        while(it != word.end())
        {
            if(isalpha(*it))
            {
                //转换小写
                *it = tolower(*it);
                ++it;
            }else{
                it = word.erase(it);
            }
        }
    }
    map<string,int>m_dict;
};

void test1()
{
    Dictionary dic;
    dic.read("The_Holy_Bible.txt");
    dic.store("dic_map.txt");
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

