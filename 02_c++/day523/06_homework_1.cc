#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;
// 编程题：vector与deque编程题
// 评委打分的例子： 要求：有五名选手ABCDE，10个评委打分，去掉最高分和最低分，求出每个选手的平均分。

// 思路：
// 1.创建Person类，定义name，score成员属性；创建五名选手存放到vector容器中；
// 2.遍历vector容器，首先10个评委的打分存放到deque容器中，sort算法对分数排序，去掉最高最低分；
// 3.deque容器遍历，进行剩余分数的累加，求平均；
// 4.输出每个选手的姓名，成绩 

class Person
{
public:
    Person(string name,double score)
    :m_name(name)
    ,m_score(score)
    {    
    }
    string m_name;  //存储姓名
    double m_score; //存储平均分数
};

//创建选手的函数
void createPerson(vector<Person> &v)
{
    string nameSeed = "ABCDE";
    for(int i =0;i<5;i++)
    {
        string name ="选手";
        name += nameSeed[i];   //将字母与“选手”字符串拼接

        double score = 0;      //初始化分数为0
        Person p(name,score);  //创建person对象
        v.push_back(p);        //将对象放入vector容器中
    }
}

//评委打分 计算平均分数
//相当于一个草稿纸，目的是去掉最高分最低分，计算平均分
//得到平均分之后再放在vector存放的Person类score数据成员里
void setScore(vector<Person> &v)
{
    for(auto it = v.begin(); it != v.end();++it)
    {
        //将10个评委的打分存储到deque中
        deque<double> d;
        for(int i =0;i < 10;++i)
        {
            //随机生成60~100之间的分数
            double score = rand()% 41 +60;
            d.push_back(score);
        }
        //排序
        sort(d.begin(),d.end());
        //去掉最高分、最低分
        //使用deque更容易操作最前和最后的数据
        d.pop_back();
        d.pop_front();
        double sum = 0;
        //遍历deque，累加剩余的分数
        for(auto dit = d.begin();dit!=d.end();++dit)
        {
            sum += *dit;
        }
        //求平均分
        double avg = sum /d.size();
        //将平均分赋值给对应的选手
        it->m_score = avg;
    }
}

//输出每个选手的姓名和成绩
void showScore(const vector<Person> &v)
{
    cout << "------最终成绩------" << endl;
    for(auto it = v.begin();it!=v.end();++it)
    {
        cout << "姓名：" << it->m_name << "\t 平均分："  << it->m_score << endl;
    }
}

int main(int argc,char *argv[])
{
    //添加随机数种子，让每次运行的打分不一样
    srand((unsigned int) time(NULL));

    //创建存储选手的vector容器
    vector<Person> v;
    //初始化5位选手
    createPerson(v);
    //评委打分，去最值，算平均
    setScore(v);
    //展示结果
    showScore(v);
    return 0;
}

