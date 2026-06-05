#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

struct compareInt
{
    bool operator()(const int &num1,const int &num2)
    {
        return num1 > num2;
    }
};


void test1()
{
    vector<int> nums = {1, 5, 8, 3, 6, 9, 2, 7, 4 };
    //先排序
    sort(nums.begin(),nums.end());
    //删除元素
    auto it = remove_if(nums.begin(),nums.end(),
    [](int num)->bool
    {
        return num > 5;
    }
    );
    nums.erase(it,nums.end());
    copy(nums.begin(),nums.end(),ostream_iterator<int>(cout, " "));
    cout << endl;

}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

