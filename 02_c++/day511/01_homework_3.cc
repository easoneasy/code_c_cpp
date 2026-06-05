#include <iostream>
using namespace std;
class Outer
{
private:
    int outerVar;
public:
    class Inner
    {
    public:
        void func(){
            Outer outer;
            outer.outerVar = 10;
            /* outerVar = 10 */
            //需要通过对象.的方式访问数据成员
        }
    };
};
void test1(){

}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

