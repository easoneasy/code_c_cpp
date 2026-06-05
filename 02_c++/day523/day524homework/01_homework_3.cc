#include <iostream>
#include <vector>

using namespace std;
// 注意vector 插入导致迭代器失效
// 给定一个 vector<int> vec = {1, 2, 3, 4, 5}，
// 使用迭代器在 vec 中所有偶数后面插入该偶数的两倍（例如：2 后面插入 4，4 后面插入 8）。
// 要求正确更新迭代器，避免迭代器失效，并输出最终结果。

void test1()
{
    vector<int> vec = {1,2,3,4,5};
    //使用普通的迭代器遍历
    auto it = vec.begin();
    while(it != vec.end())
    {
        if(*it % 2 == 0)
        {
            //发现偶数，计算出它的两倍
            int targetValue = *it * 2;
            //在偶数的后面插入2倍，更新迭代器
            auto newIt = vec.insert(it + 1 ,targetValue);
            //此时newIt指向新插入元素，下一次循环应该跳过这个元素
            it = newIt + 1;
        }
        else{
            //如果是奇数，就将迭代器向后移动一位
            ++it;
        }
    }

    //输出最后结果
    cout << "-------最终的vector结果-------" << endl;
    for(auto e : vec)
    {
        cout << e << " ";
    }
    cout << endl;
}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

