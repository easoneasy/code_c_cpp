#include <iostream>
#include <set>

using namespace std;

//int、double通用模板
template<typename T>
T add(const T &t1 , const T &t2)
{
    cout << "normal template" << endl;
    return t1 + t2;
}
//特殊模板
template<>
set<int> add<set<int>>(const set<int> &s1,const set<int> &s2)
{
    cout << "special template" << endl;
    //初始化结果集，直接复制第一个set的内容放入result中
    set<int> result = s1;
    //将第二个set的元素依次插入到结果集中
    result.insert(s2.begin(),s2.end());
    return result;
}
//辅助打印set元素的函数模板
template <typename T>
void printSet(const set<T> &s)
{
    cout << "{" ;
    for(auto &e:s)
    {
        cout << e << " " ;
    }
    cout << "}" << endl;
}

void test1()
{
    cout << add(1,2) << endl;
    cout << add(1.1,2.2) << endl;
    set<int> set1 = {1,2,3};
    set<int> set2 = {4,5,6};
    set <int> res = add(set1,set2);
    printSet(res);
}

int main(int argc,char *argv[])
{

    test1();
    return 0;
}

