#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class PersonInfo
{
public:
    PersonInfo() = default;
    void setName(string &name)
    {
        m_name = name;
    }
    void setPhones(vector<string> & phones)
    {
        m_phones = phones;
    }
    void print()
    {
        cout << "姓名："  << m_name << " | 电话： ";
        for(const auto &phone :m_phones)
        {
            cout << phone << " " ;
        }
        cout << endl;
    }
private:
    string m_name;
    vector<string> m_phones;
};
void test1(){
    ifstream ifs{"phone.txt"};

    vector<PersonInfo> personInfos;
    string line;
    while(getline(ifs,line))
    {
        istringstream iss{line};
        string name;
        string phone;
        //创建临时vector，将其赋值给类中的vector存储
        //每次循环都会重新创建vector
        vector<string> phones;
        iss >> name;
        //循环读取phone
        while(iss >> phone)
        {
            phones.push_back(phone);
        }
        //每次都创建新对象，while循环之后会自动销毁
        PersonInfo info;
        info.setName(name);
        info.setPhones(phones);
        //把临时对象放入个人信息的vector中
        personInfos.push_back(info);

    }
    cout << "----通讯录信息-----" << endl;
    for(auto &person : personInfos)
    {
        person.print();
    }

    ifs.close();
}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

