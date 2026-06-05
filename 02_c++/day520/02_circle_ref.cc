#include <iostream>
#include <memory>
using namespace std;

/*
    循环引用问题
*/

class Child;

class Parent
{
public:
    // shared_ptr<Child> m_spChild;
    weak_ptr<Child> m_spChild;
};

class Child
{
public:
    shared_ptr<Parent> m_spParent;
};

//环状引用
void test1()
{   
    //在程序结束时会自动销毁栈对象
    shared_ptr<Parent> parentPtr{new Parent{}};
    shared_ptr<Child> childPtr{new Child{}};
    cout << "parent count : " << parentPtr.use_count() << endl;
    cout << "child count : " << childPtr.use_count() << endl;

    cout << "---------------------------" << endl;

    //进行赋值
    parentPtr->m_spChild = childPtr;
    childPtr->m_spParent = parentPtr;
    cout << "parent count : " << parentPtr.use_count() << endl;
    cout << "child count : " << childPtr.use_count() << endl;
    //parentPtr、childPtr（栈对象）会自动销毁，但指向的对象还有指针指向
    //并没有被释放，所以会造成内存泄漏

}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

