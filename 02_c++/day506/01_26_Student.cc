#include <iostream>
#include <string.h>
using namespace std;

class Student
{
public:
    //构造函数
    Student(const string name , int num ,double score)
    :m_num(num)
    ,m_score(score)
    {
        cout << "Student(string,int,double)" << endl;
        //字符串拷贝
        m_name = name;
    }
    //打印
    void print()
    {
        cout << m_name <<" "<< m_num << " " << m_score << endl;
    }

private:
    string m_name;
    int m_num;
    double m_score;
};

int main(int argc,char *argv[])
{
    string name1 = "zs";
    Student s1{name1,1,99};
    s1.print();

    return 0;
}

