#include <iostream>
using namespace std;

class MyClass
{
public:
    void operator()()
    {
        cout << "operator()()" << endl;
        count++;
    }

    void operator()(int num)
    {
        cout << "operator()(int)" << endl;
        cout << "num=" << num << endl;
        count++;
    }
    int count = 0;
};
void test1(){
    MyClass obj;
    obj();
    obj();
    cout << obj.count << endl;

}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

