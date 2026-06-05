#include <iostream>
#include <string.h>

using namespace std;
class String {
public:
    String(const char * pstr)
    {
        m_size = strlen(pstr);
        //小于15，使用buff中的local来存字符数据
        if(m_size <= 15)
        {
            m_capacity = 15;
            memset(m_buffer.m_local,0,sizeof(m_buffer.m_local));
            strcpy(m_buffer.m_local,pstr);
        }else{
            //大于15，用堆空间存字符数据，buff中的point指针指向
            m_capacity = m_size;
            m_buffer.m_pointer = new char[strlen(pstr) + 1]{};
            strcpy(m_buffer.m_pointer,pstr);
        }
    }
    String(const String &rhs)
    :m_size(rhs.m_size)
    ,m_capacity(rhs.m_capacity)
    {
        if(m_size <= 15)
        {
            memset(m_buffer.m_local,0,sizeof(m_buffer.m_local));
            strcpy(m_buffer.m_local,rhs.m_buffer.m_local);
        }else{
            m_buffer.m_pointer = new char[rhs.m_capacity + 1]{};
            strcpy(m_buffer.m_pointer,rhs.m_buffer.m_pointer);
        }
    }
    ~String()
    {
        if(m_size > 15)
        {
            delete [] m_buffer.m_pointer;
            m_buffer.m_pointer = nullptr;
        }
    }
    char & operator[](size_t idx)
    {
        if(idx > m_size -1)
        {
            cout << "out of range " << endl;
            static char nullchar = '\0';
            return nullchar;
        }
        if(m_size > 15)
        {
            return m_buffer.m_pointer[idx];
        }else{
            return m_buffer.m_local[idx];
        }
    }

    friend
    ostream & operator<<(ostream & os,const String & rhs);
private:
	union Buffer{
		char * m_pointer;
		char m_local[16];
	};
	
	size_t m_size;
	size_t m_capacity;
    Buffer m_buffer;
};

ostream & operator<<(ostream &os,const String &rhs)
{
    if(rhs.m_size > 15)
    {
        os << rhs.m_buffer.m_pointer;
    }else{
        os << rhs.m_buffer.m_local;
    }
    return os;
}

void test0(){
    String str1("hello");
    String str2("hello,world!!!!!");
    String str3 = str1;
    cout << "str1 : " << str1 << endl;
    cout << "str3 : " << str3 << endl;
    String str4 = str2;
    str2[4] = 'x';
    cout << "str2 : " << str2 << endl;
    cout << "str4 : " << str4 << endl;
}

int main(int argc,char *argv[])
{
    test0();

    return 0;
}

