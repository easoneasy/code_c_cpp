#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class CountEven
{
public:
    CountEven()
    : m_count(0)
    , m_callCount(0)
    {
        cout << "CountEven" << endl;
    }
    
    void operator()(int val)
    {
        m_callCount++;
        //是偶数就++
        if(val % 2== 0)
        {
            m_count++;
        }
    }

    int getCount() const
    {
        return m_count;
    }

    int getCallCount() const
    {
        return m_callCount;
    }

private:
    int m_count; // 偶数的个数
    int m_callCount;    // 调用次数
};
void test1(){
    vector<int> vec{1,2,3,4,5,6,7,8,9,10};
    CountEven counter = for_each(vec.begin(),vec.end(),CountEven());
    CountEven ce;
    for(auto &val :vec)
    {
        ce(val);
    }
    cout << ce.getCallCount() << endl;
    cout << ce.getCount() << endl;
    cout << "---------------" << endl;
    cout << counter.getCallCount() << endl;
    cout << counter.getCount() << endl;


}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

