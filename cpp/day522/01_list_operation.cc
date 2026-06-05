#include <iostream>
#include <list>
#include <deque>
#include <algorithm>
using namespace std;

template<typename Container>
void print(Container &box)
{
    for(auto &e : box)
    {
        cout << e << " " ;
    }
    cout << endl;
}

//List特有的操作
//sort排序，默认升序，内置类型直接用
void test1()
{
    list<int> box{2,7,4,3,1};
    print(box);
    cout << "------sort------" << endl;
    box.sort();
    print(box);
}

class Student
{
public:
    //构造函数
    Student(int id , string name , int age)
    :m_id(id)
    ,m_name(name)
    ,m_age(age)
    {
        
    }
    friend
    ostream &operator<<(ostream &os,Student &s);

    //重载 < 运算符
    bool operator<(const Student & s)
    {
        return this->m_id < s.m_id;
    }

    friend struct StudentCompare;
private:
    int m_id;
    string m_name;
    int m_age;
};

//重载输出运算符
ostream &operator<<(ostream &os ,Student &s)
{
    cout << s.m_id << " " << s.m_name << " " << s.m_age << endl;
    return os;
}

//自定义类型的排序 sort()
void test2()
{
    Student s1{2,"zs",20};
    Student s2{7,"ls",22};
    Student s3{5,"zs",19};
    Student s4{1,"zs",23};
    list<Student> box{s1,s2,s3,s4};
    print(box);
    cout << "------sort------" << endl;
    //重载 < 运算符
    box.sort();
    print(box);
}

//自定义比较器
struct StudentCompare
{
    bool operator()(const Student &lhs,const Student &rhs)
    {
        return lhs.m_age < rhs.m_age;
    }
};

void test3()
{
    Student s1{2,"zs",20};
    Student s2{7,"ls",22};
    Student s3{5,"zs",19};
    Student s4{1,"zs",23};
    list<Student> box{s1,s2,s3,s4};
    print(box);
    cout << "------sort------" << endl;
    //使用sort+比较器
    box.sort(StudentCompare());
    print(box);
}

//deque排序
void test4()
{
    deque<int> box{7,6,4,4,5};
    print(box);
    cout << "-------sort-------" << endl;
    sort(box.begin(),box.end());
    print(box);
}

int main(int argc,char *argv[])
{

    // test1();
    // test2();
    // test3();
    test4();

    return 0;
}

