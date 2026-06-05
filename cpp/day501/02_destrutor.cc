#include <string.h>
#include <iostream>
using namespace std;

class Student
{
public:
    //构造函数
    Student(int age,const char *name)
    :m_age(age)
    ,m_name(new char[strlen(name)+1]{})
    {
        cout << "Student(int,char)" << endl;
        strcpy(m_name,name);
    }
    //析构函数
    ~Student()
    {
        cout << "~Student" << endl;
        if(m_name)
        {
            delete [] m_name;
            m_name = nullptr;
        }
    }
    void getStudent(){
        cout << "name: " << m_name << "  " << "age: " << m_age << endl;
    }

private:
    int m_age;
    char *m_name;
};
void test1(){
    Student s1(20,"zs");
    s1.getStudent();
    Student *s2 = new Student{21,"ls"};
    s2->getStudent();
    delete s2;
    s2 = nullptr;

}

int main(int argc,char *argv[])
{
    test1();



    return 0;
}

