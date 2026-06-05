#include <iostream>
#include <map>
#include <utility>
#include <vector>
using namespace std;
void visitMap(map<int,string> &map)
{
    for(auto &e : map)
    {
        cout << e.first << " = " << e.second << endl;
    }
    cout << endl;
}
void test1()
{
    map<int,string> m1;
    map<int,string> m2{
        pair<int,string>{3,"aa"},
        pair<int,string>{5,"dd"},
        pair<int,string>{2,"gg"}
    };
    visitMap(m1);
    cout << "------------" << endl;
    visitMap(m2);

    map<int,string>m3{
        {3,"aa"},
        {5,"dd"},
        {2,"gg"}
    };
    cout << "------------" << endl;
    visitMap(m3);
    map<int,string> m4{
        std::make_pair(2,"aaa"),
        std::make_pair(1,"bb"),
        std::make_pair(3,"dda")
    };
    cout << "------------" << endl;
    visitMap(m4);
    map<int,string>m5{m4.begin(),m4.end()};
    cout << "------------" << endl;
    visitMap(m5);

    map<int,string> m6{m4};
    cout << "------------" << endl;
    visitMap(m6);
}
void test2()
{
    map<int,string> m1{
        {2,"aaa"},
        {1,"ddd"}
    };
    auto it = m1.begin();
    for(;it != m1.end();++it)
    {
        cout << it->first ;
        cout << it->second << endl;
    }
}

void test3()
{
    map<int,string> m{
        {2,"zs"},
        {5,"ls"},
        {4,"ww"}
    };
    int result = m.count(3);
    if(result)
    {
        cout << "find success" << endl;

    }else{
        cout << "not found" << endl;
    }

    auto it = m.find(2);
    if(it != m.end())
    {
        cout << "find success " << endl;
        cout << it->first << " = " << it->second << endl;
    }

}

void test4()
{
    map<int,string> m;
    m.insert({3,"ls"});
    m.insert({
        {6,"qq"},
        {3,"aa"},
        {4,"cc"}
    });
    for(auto &e :m)
    {
        cout << e.first << " = " << e.second << endl;
    }

}
void test5()
{
    map<int,string> m{
        {2,"zs"},        
        {5,"zs"},        
        {1,"ls"},        
        {3,"ww"}
    };
    m[2] = "zss";
    cout << m[2] << endl;

    map<string,string> m2{
        {"city", "BJ"},
        {"name", "zs"},
        {"gender", "male"},
    };
    cout << m2["city"] << endl;
    cout << "======"<< endl;
    m2["age"] = "20";
    for(auto &e : m2)
    {
        cout << e.first << " = " << e.second << endl;
    }
}

int main(int argc,char *argv[])
{
    // test1();
    // test2();
    // test3();
    // test4();
    test5();

    return 0;
}