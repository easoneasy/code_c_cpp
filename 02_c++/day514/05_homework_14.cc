#include <iostream>
#include <string.h>
using namespace std;

class Person
{
public:
    //构造函数
    Person(const char *name,int age)
    :m_name(new char[strlen(name)+1]{})
    ,m_age(age)
    {
        cout << "Person" << endl;
        strcpy(m_name,name);
    }
    //析构函数
    ~Person()
    {
        if(m_name)
        {
            delete [] m_name;
            m_name =nullptr;
        }
    }
    //拷贝构造函数
    Person(const Person &rhs)
    :m_name(new char[strlen(rhs.m_name)+1]{})
    ,m_age(rhs.m_age)
    {
        cout << "Person(const Person &)" << endl;
        strcpy(m_name,rhs.m_name);
    }
    //赋值运算符函数
    Person &operator=(const Person &rhs)
    {   
        //自赋值判断
        if(this != &rhs)
        {
            delete [] m_name;
            //深拷贝
            m_name = new char[strlen(rhs.m_name)+1]{};
            strcpy(m_name,rhs.m_name);
            m_age=rhs.m_age;
        }
        return *this;
    }
    virtual void display()
    {
        cout << "name : "<< m_name << " age : " << m_age << endl;
    }
private:
    char *m_name;
    int m_age;
};

class Employee
:public Person
{
public:
    //构造函数
    Employee(const char*name,int age,const char *dept,int salary)
    :Person(name,age)
    ,m_dept(new char[strlen(dept)+1]{})
    ,m_salary(salary)
    {
        cout << "Employee" << endl;
        total_salary += m_salary;
        member_count +=1;
    }
    //析构函数
    ~Employee()
    {
        if(m_dept)
        {
            delete [] m_dept;
            m_dept = nullptr;
            total_salary -= m_salary;
            member_count -= 1;
        }
    }
    //拷贝构造函数
    Employee(const Employee &rhs)
    :Person(rhs)
    ,m_dept(new char[strlen(rhs.m_dept)+1]{})
    ,m_salary(rhs.m_salary)
    {
        cout << "Employee(consy Employee &)" << endl;
        strcpy(m_dept,rhs.m_dept);
        total_salary += m_salary;
        member_count +=1;
    }
    //赋值运算符函数
    Employee &operator=(const Employee &rhs)
    {
        if(this != &rhs)
        {
            Person::operator=(rhs);
            char *tmp = new char[strlen(rhs.m_dept)+1]{};
            strcpy(tmp,rhs.m_dept);
            delete [] m_dept;
            total_salary -= m_salary;
            m_dept = tmp;
            m_salary = rhs.m_salary;
            total_salary += m_salary;
        }
        return *this;
    }
    virtual void display() override
    {
        Person::display();
        cout << "dept : "<< m_dept << " salary : " << m_salary << endl;
    }
    static double getAverageSalary()
    {
        if(member_count == 0)
        {
            return 0.0;
        }
        return total_salary / member_count;
    }
private:
    char *m_dept;
    int m_salary;
    static double total_salary;
    static int member_count;
};

double Employee::total_salary = 0;
int Employee::member_count = 0;

void test1()
{
    Employee emp1("张三", 30, "研发部", 10000);
    Employee emp2("李四", 25, "市场部", 8000);

    emp1.display();
    cout << "------------" << endl;
    emp2.display();
    emp2 = emp1; 
    emp2.display();
    
    cout << "当前平均工资: " << Employee::getAverageSalary() << endl;
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

