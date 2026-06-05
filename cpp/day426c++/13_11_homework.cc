#include <string.h>
#include <iostream>
using namespace std;

class Student{

public:
    //构造函数
    Student(const char *name,int num,int age)
    :m_name(new char[strlen(name)+1]{})
    ,m_num(num)
    ,m_age(age){
        strcpy(m_name,name);
        m_num = num;
        m_age = age;
        cout << m_name << "    constructor" << endl;
    }
    void print(){
        cout << m_name << " " << m_num << " " << m_age << endl;
    }
    //析构函数
    ~Student(){
        if(m_name){
            cout << m_name << "    ~Student()" << endl;
            delete [] m_name;
            m_name = nullptr;
        }
    }
private:
    char *m_name;
    int m_num;
    int m_age;
};
//全局变量
Student s1("s1",1,11);

void test1(){
    s1.print();
    //局部变量
    Student s2("s2",2,22);
    s2.print();
    //静态变量
    static Student s3("s3",3,33);
    s3.print();
    //堆上变量
    Student *s4 = new Student{"s4",4,44};
    s4->print();
    delete s4;
    s4 = nullptr;
}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}
