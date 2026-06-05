#include <iostream>
#include <string.h>
using namespace std;

class CowString
{
    //定义代理类 
    //让其判断是只读还是修改
    //如果是调用=就说明是修改
    //如果是>> 就说明是只读
    class CharProxy
    {
    public:
        CharProxy(CowString &cow ,int index)
        :m_self(cow)
        ,m_index(index)
        {
            cout << "CharProxy" << endl;
        }

    //将输出重载声明为友元
    friend
    ostream &operator<<(ostream &os,const CharProxy &rhs);
    
    //重载赋值运算符
    char &operator=(const char &ch)
    {
        if(m_index < 0 || m_index >=strlen(m_self.m_pStr))
        {
            static char nullchar = '\0';
            return nullchar;
        }else{
            //获取引用计数，是否大于1
            //如果大于1，说明有共享
            if(m_self.getRefCount() > 1)
            {
                //计数器-1
                m_self.decrementRefCount();
                //深拷贝
                char *tmp = new char[4 + strlen(m_self.m_pStr) + 1 ]{} +4;
                strcpy(tmp,m_self.m_pStr);
                m_self.m_pStr = tmp;
                m_self.initRefCount();
            }
            m_self.m_pStr[m_index] = ch;
            return m_self.m_pStr[m_index];
        }
    }
    private:
        CowString &m_self;
        int m_index;
    };

    public:

        //无参构造函数
        CowString()
        :m_pStr(new char[4 + 1]{} + 4)
        {
            cout << "CowString" << endl;
            //初始化引用计数
            initRefCount();
        }
        //有参构造函数
        CowString(const char *pStr)
        :m_pStr(new char[4+ strlen(pStr)+1]{} +4)
        {
            cout << "CowString(const char *)" << endl;
            //初始化引用计数
            initRefCount();
            //将数据复制到申请的堆空间中
            strcpy(m_pStr,pStr);
        }
        //析构函数
        ~CowString()
        {
            //将引用计数- 1
            decrementRefCount();
            //如果引用计数为0，就回收资源
            if(getRefCount()== 0)
            {
                //释放资源（加上计数器的资源也要释放掉）
                delete [] (m_pStr-4);
                cout << "------- release heap -------" << endl;
            }
            //将指针置空
            m_pStr = nullptr;
        }
        //拷贝构造函数
        CowString(const CowString &rhs)
        :m_pStr(rhs.m_pStr)   //将本对象的指针，指向要赋值的对象的数据空间，浅拷贝
        {
            cout << "CowString(const CowString)" << endl;
            //引用计数器+1
            incrementRefCount();
        }
        //赋值运算符函数
        CowString &operator=(const CowString &rhs)
        {
            //自赋值判断
            if(this != &rhs)
            {
                //先将本身的计数器-1
                decrementRefCount();
                //再判断计数器是否为0
                if(getRefCount() == 0)
                {
                    //如果为0可以直接释放资源,更改指针的指向
                    delete [] (m_pStr-4);
                }
                //如果不为0可以将指针指向新的共享空间
                m_pStr = rhs.m_pStr;
                //再将新共享空间的引用计数器+1
                incrementRefCount();
            }
            //返回当前对象
            return *this;
        }

        //重载下标访问符[]
        CharProxy operator[](int index)
        {
            return CharProxy{*this,index};
        }

        //将输出重载设置为友元
        friend
        ostream &operator<<(ostream &os , CowString &cs);

        //获取字符串长度的方法
        int size()
        {
            return strlen(m_pStr);
        }
        //返回c风格的字符串
        char * c_str()
        {
            return m_pStr;
        }
        //获取引用计数的值
        int getRefCount()
        {
            return *(int *)(m_pStr - 4);
        }
        friend
        ostream &operator<<(ostream &os,const CowString::CharProxy &rhs);
    private:
        //初始化引用计数器
        void initRefCount()
        {
            //将m_pStr - 4 指针指向前面int的位置，
            //(int *)将char*强制类型转换成int*
            //最后再将指针解引用，赋值为1
            *(int *)(m_pStr - 4) = 1;

        }
        //引用计数+1
        void incrementRefCount()
        {
            ++ *(int *)(m_pStr - 4);
        }
        //引用计数-1
        void decrementRefCount()
        {
            -- *(int *)(m_pStr - 4);
        }
        char *m_pStr;
};

//输出重载
ostream &operator<<(ostream &os , CowString &cs)
{
    os << cs.m_pStr;
    return os;
}

//CharProxy类的Operator<< 重载
ostream &operator<<(ostream &os,const CowString::CharProxy &rhs)
{
    os << rhs.m_self.m_pStr[rhs.m_index];
    return os;
}

void test1(){
    CowString cs1 ={"abcd"};
    CowString cs2 = {"hello"};
    CowString cs3 = cs2;
    cs2 = cs1;
    cout << cs1 << "  RefCount : " << cs1.getRefCount() <<  endl;
    cout << cs2 << "  RefCount : " << cs2.getRefCount() << endl;
    cout << cs3 << "  RefCount : " << cs3.getRefCount() <<  endl;
    cout << cs2[0] << endl;
    cs2[0]='A';
    cout << "cs1: " << cs1 << endl;
    cout << "cs2: " << cs2 << endl;
}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

