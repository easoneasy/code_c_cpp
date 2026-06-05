#include <iostream>
using namespace std;

class Singleton
{
public:
    static Singleton &getInstance()
    {
        static Singleton instance;
        return instance;
    }
    //删除复制控制的函数
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
private:
    Singleton(){
        cout << "Singleton" << endl;
    }
};
void test1(){
    cout << &Singleton::getInstance()<< endl;
}

int main(int argc,char *argv[])
{
    test1();



    return 0;
}

