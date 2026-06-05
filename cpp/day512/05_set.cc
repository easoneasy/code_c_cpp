#include <iostream>
#include<set>
#include<string>
using namespace std;

void test1(){
    set<int>box{2,5,3,1,4,3};
    for(auto &element:box)
    {
        cout << element << " " ;
    }
    cout << endl;
    //count(元素)
    //找到了就返回1，找不到返回0
    int result = box.count(4);
    cout << result << endl;
    if(result)
    {
        cout << "find success" << endl;
    }else{
        cout << "not found" << endl;
    }
    cout << "-------" << endl;
    auto it = box.find(3);
    if(it != box.end())
    {
        cout << "find success" << endl;
        cout << *it << endl;
    }else{
        cout << "not found" << endl;
    }
}
//增强for循环
void visitSet(set<int> &box)
{
    for(auto &e : box)
    {
        cout << e << " " ;
    }
    cout << endl;
}

void test2()
{
    set<int> box;
    box.insert(1);
    box.insert(2);
    visitSet(box);
    box.insert({5,7,5,6,9,0});
    visitSet(box);
    cout << "------" << endl;
    pair<set<int>::iterator,bool> p = box.insert(100);
    if(p.second)
    {
        cout << "insert success" << endl;
        cout << *(p.first) << endl;
    }else{
        cout << "insert failed." << endl;
    }
}

//存储一对数据
void test3()
{
    pair<string,int> p {"age",20};
    cout << p.first << " " << p.second << endl;
}

//erase删除
void test4()
{
    set<int> box{1,2,5,3,4};
    visitSet(box);
    auto it = box.begin();
    ++it;
    ++it;
    box.erase(it);
    visitSet(box);
}
void test5()
{
    set<string>box{"aa","bb","cc"};
    for(auto &e:box)
    {
        cout << e << " ";
    }
    cout << endl;
}
class Student
{
public:
    Student(int id,string name,int age)
    :m_id(id)
    ,m_name(name)
    ,m_age(age)
    {
        cout << "Student(int,string,int)"<< endl;
    }
    void print()
    {
        cout << m_id << " " << m_name << " " << m_age << endl;
    }
    int m_id;
    string m_name;
    int m_age;
};

bool operator<(const Student &s1,const Student &s2)
{
    return s1.m_age < s2.m_age;
}

void test6()
{
    set<Student> box;
    box.insert(Student{6,"cc",20});
    box.insert(Student{4,"aa",21});
    box.insert(Student{1,"bb",22});
    for(Student e : box)
    {
        e.print();
    }
}
int main(int argc,char *argv[])
{
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    test6();

    return 0;
}

