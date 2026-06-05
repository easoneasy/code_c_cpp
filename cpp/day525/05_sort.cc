#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <iterator>
#include <deque>
using namespace std;

// sort
void test1()
{
    deque<int> box{3, 5, 1, 4, 2, 1};
    sort(box.begin(), box.end());
    copy(box.begin(), box.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

// max / min 返回最大最小值
void test2()
{
    int a = 1;
    int b = 2;
    int maxValue = max(a, b);
    cout << "maxValue : " << maxValue << endl;
    int minValue = min(a, b);
    cout << "minValue : " << minValue << endl;
}

class Student
{
public:
    Student(string name, int age)
        : m_name(name), m_age(age)
    {
    }
    string m_name;
    int m_age;
};
// 重载 <<
ostream &operator<<(ostream &os, const Student &s)
{
    os << s.m_name << " " << s.m_age << endl;
    return os;
}
// 自定义比较器
struct StudentCompare
{
    bool operator()(const Student &s1, const Student &s2) const
    {
        return s1.m_age < s2.m_age;
    }
};

void test3()
{
    Student s1{"zs", 19};
    Student s2{"ls", 21};
    const Student &maxStudent = max(s1, s2, StudentCompare());
    cout << maxStudent;
}

// lower_bound 二分查找第一个 >= 目标值的元素
// upper_bound 二分查找第一个 > 目标值的元素
// equal_range 二分查找 = 目标值的元素范围的迭代器对 pair 对象
void test4()
{
    vector<int> box{1,2,3,4,5};
    auto it = lower_bound(box.begin(),box.end(),3);
    cout << " it =  " << *it << endl;
    cout << " --------------------- " << endl;
    auto it2 = upper_bound(box.begin(),box.end(),3);
    cout << " it2 =  " << *it2 << endl;
    cout << " --------------------- " << endl;
}

//equal_range 二分查找等于目标值的元素范围的迭代器对  pair对象
//返回值为pair对象，first是指向第一个 >= 目标元素的位置
//second是指向第一个 > 目标元素的位置
void test5()
{
    vector<int> box{1,2,3,3,3,4,5};
    auto p = equal_range(box.begin(),box.end(),3);
    auto itStart = p.first;
    auto itEnd = p.second;
    cout << *itStart << endl;
    cout << *itEnd << endl;
    cout << "------------" << endl;
    copy(itStart,itEnd,ostream_iterator<int>(cout," "));
    cout << endl;
}

int main(int argc, char *argv[])
{

    // test1();
    // test2();
    // test3();
    test4();
    test5();

    return 0;
}
