#include <iostream>
#include <list>
#include <deque>
using namespace std;
//编程题：deque与list的简单使用
//编写程序，从一个 list 拷贝元素到两个 deque 中。
//值为偶数的所有元素都拷贝到一个 deque 中，而奇数值元素都拷贝到另一个 deque 中

void test1()
{
    // 初始化一个包含奇数、偶数（以及负数）的 list
    list<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -3, -4};

    // 创建两个空的 deque 分别存放偶数和奇数
    deque<int> even_deque;
    deque<int> odd_deque;

    // 遍历 list 并根据奇偶性拷贝元素
    for (const auto& val : numbers) {
        if (val % 2 == 0) {
            even_deque.push_back(val); // 偶数存入 even_deque
        } else {
            odd_deque.push_back(val);  // 奇数存入 odd_deque
        }
    }

    // 打印验证结果
    cout << "偶数 deque 里的元素: ";
    for (int num : even_deque) {
        cout << num << " ";
    }
    cout << "\n奇数 deque 里的元素: ";
    for (int num : odd_deque) {
        cout << num << " ";
    }
    cout << endl;

}

int main(int argc,char *argv[])
{

    test1();

    return 0;
}

