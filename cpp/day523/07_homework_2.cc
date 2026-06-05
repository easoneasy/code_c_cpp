#include <iostream>
#include <list>
#include <string>
#include <algorithm>
using namespace std;
// 编程题：list实战
// 学生成绩管理系统
// 题目要求：
// 1 .制作一个学生成绩单管理系统
// 2 .将student自定义数据类型进行排序，
// student中属性有姓名、语文成绩、数学成绩、英语成绩、总成绩。

// 排序规则：按照总成绩sum进行降序，如果总成绩sum相同按照语文成绩进行降序

class Student
{
public:
    Student(string name,int Chinese,int math,int english)
    :m_Name(name)
    ,m_Chinese(Chinese)
    ,m_Math(math)
    ,m_English(english)
    ,m_Sum(Chinese + math + english)
    {
    }

    string m_Name;
    int m_Chinese;
    int m_Math;
    int m_English;
    int m_Sum;
};

//自定义排序规则
//按总成绩降序，总成绩相同，按语文成绩降序
bool compareStudent(const Student &s1,const Student &s2)
{
    if(s1.m_Sum == s2.m_Sum)
    {
        return s1.m_Chinese > s2.m_Chinese;
    }
    return s1.m_Sum > s2.m_Sum;
}

// 打印学生成绩单的函数
void printList(const list<Student>& L) {
    cout << "----------------------- 学生成绩单 -----------------------" << endl;
    cout << "姓名\t语文\t数学\t英语\t总成绩" << endl;
    
    for (list<Student>::const_iterator it = L.begin(); it != L.end(); it++) {
        cout << it->m_Name << "\t"
             << it->m_Chinese << "\t"
             << it->m_Math << "\t"
             << it->m_English << "\t"
             << it->m_Sum << endl;
    }
    cout << "--------------------------------------------------------" << endl;
}

void test1()
{
    // 创建存储学生的 list 容器
    list<Student> L;

    // 准备测试数据
    // 特意设置了总分相同、语文不同的情况，以及完全不同和完全相同的情况来验证排序规则
    Student s1("张三", 90, 80, 90); // 总分 260
    Student s2("李四", 85, 85, 90); // 总分 260 (总分相同，张三语文90 > 李四语文85)
    Student s3("王五", 100, 100, 100); // 总分 300
    Student s4("赵六", 60, 70, 80); // 总分 210
    Student s5("孙七", 85, 85, 90); // 总分 260 (与李四完全并列)
    Student s6("周八", 70, 95, 95); // 总分 260 (总分相同，语文70最低)

    // 将数据插入到 list 容器中
    L.push_back(s1);
    L.push_back(s2);
    L.push_back(s3);
    L.push_back(s4);
    L.push_back(s5);
    L.push_back(s6);

    cout << "排序前：" << endl;
    printList(L);

    // 3. 进行排序
    // 记住：链表容器不能使用标准的 std::sort(L.begin(), L.end())
    // 必须使用链表自身的成员函数 sort()
    L.sort(compareStudent);
    
    cout << endl << "排序后（规则：总分降序 -> 语文降序）：" << endl;
    printList(L);
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

