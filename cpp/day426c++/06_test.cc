#include <iostream>
using namespace std;

namespace Math{
        void add(int x ,int y){
            cout << x + y <<endl;
        }
        void subtract(int x ,int y){
            cout << x - y << endl;
        }
    }

int main(int argc,char *argv[])
{
    using Math::add;
    using Math::subtract;

    add(1,2);
    subtract(4,3);


    return 0;
}

