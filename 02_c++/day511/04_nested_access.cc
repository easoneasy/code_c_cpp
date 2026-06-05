#include <iostream>
using namespace std;

class Outer
{
public:

    //public修饰的内部类
    class Inner1
    {
        public:
            void inner1Method1()
            {
                cout << "inner1Method1" << endl;
                //内部类的内部，访问外部类成员
                Outer outer1;
                outer1.m_outerNum1;
                outer1.outerMethod1();
                outer1.m_outerNum2;
                outer1.outerMethod2();
            }
            friend
            void test1();
            friend
            class Outer;
            int m_inner1Num1;

        private:
            void inner1Method2()
            {
                cout << "inner1Method2" << endl;
            }

            int m_inner1Num2;
    };
        friend
        void test1();

private:
    //private修饰的内部类
    class Inner2
    {
    public:
        void inner2Method1()
        {
            cout << "inner2Method1" << endl;
                Outer outer1;
                outer1.m_outerNum1;
                outer1.outerMethod1();
                outer1.m_outerNum2;
                outer1.outerMethod2();
        }
        int m_inner2Num1;

        friend
        void test1();
        friend
            class Outer;


    private:
        void inner2Method2()
        {
            cout << "inner2Method2" << endl;
        }
        int m_inner2Num2;
    };
public:
    //外部类的成员
    int m_outerNum1;
    void outerMethod1()
    {
        cout << "outerMethod1" << endl;
        //在外部类的内部访问内部类成员
        //无法访问内部类的私有成员
        Inner1 inner1;
        inner1.inner1Method1();
        inner1.inner1Method2();
        inner1.m_inner1Num1=10;
        inner1.m_inner1Num2=10;

        Inner2 inner2;
        inner2.inner2Method1();
        inner2.inner2Method2();
        inner2.m_inner2Num1=10;
        inner2.m_inner2Num2=10;
    }
private:
    int m_outerNum2;
    void outerMethod2()
    {
        cout << "outerMethod2" << endl;
    }
};
void test1(){

    //在外部类的外部访问内部类成员
    //只能访问内部类的公有成员,私有成员需要使用友元
    Outer::Inner1 inner1;
    inner1.inner1Method1();
    inner1.inner1Method2();
    inner1.m_inner1Num1 = 10;
    //访问不了内部类的私有成员,私有成员需要使用友元
    //创建内部类对象时，需要在外部类声明友元
    Outer::Inner2 inner2;
    inner2.inner2Method1();
    inner2.inner2Method2();
}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

