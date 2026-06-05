#include <iostream>
#include<vector>
using namespace std;

void test1(){
    vector<int> box{1,2,3,4,5};
    cout << box.size() << endl;
    cout << box.capacity() << endl;
    cout << box.empty() << endl;
    for(auto & element:box)
    {
        cout << element;
    }
    cout << endl;
    box.push_back(6);
    cout << box.size() << endl;
    cout << box.capacity() << endl;

}
int main(int argc,char *argv[])
{
    test1();



    return 0;
}

