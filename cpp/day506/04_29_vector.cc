#include <iostream>
#include<vector>
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
    //拷贝构造函数
    Student(const Student &rhs)
    :m_num(rhs.m_num)
     ,m_score(rhs.m_score)
    {
        m_name = rhs.m_name;
        cout << "Student(const Student &)" << endl;
    }
    //析构函数
    ~Student()
    {
        cout << "~Student" << endl;
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
    Student s1{"zs",1,80};
    Student s2{"ls",2,90};
    Student s3{"ww",3,89};
    vector<Student> box;
    cout << box.size() << endl;
    cout << box.capacity() << endl;
    box.push_back(s1);
    cout << box.size() << endl;
    cout << box.capacity() << endl;
    box.push_back(s2);
    box.push_back(s3);
    cout << box.size() << endl;
    cout << box.capacity() << endl;
    //增强for循环遍历vector
    for(auto &element :box)
    {
        element.print();
    }
    cout << "-----------" << endl;
    //迭代器遍历vector
    auto itBegin = box.begin();
    for(;itBegin!=box.end();itBegin++)
    {
        itBegin->print();
    }
    cout << "-----------" << endl;
    box.push_back({"zz",4,99});
    for(auto &element : box)
    {
        element.print();
    }
    cout << "-----------" << endl;
    
    auto itBgein1 = box.begin();
    for(;itBgein1!=box.end();++itBgein1)
    {
        itBgein1->print();
    }
    return 0;
}

