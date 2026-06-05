#include <iostream>
#include<string.h>
using namespace std;

class String
{
public:
    //无参构造函数
	String()
    /* :_pstr(nullptr) */
    {
        cout << "String()" << endl;
    }
    //char构造函数
	String(const char *pstr)
    :_pstr(new char[strlen(pstr)+1]{})
    {
        cout << "String(const char *)" << endl;
        strcpy(_pstr,pstr);
    }
    //拷贝构造函数
	String(const String &rhs)
    :_pstr(new char[strlen(rhs._pstr)+1]{})
    {
        cout << "String(const String &)" << endl;
        strcpy(_pstr,rhs._pstr);
    }
	String &operator=(const String &rhs)
    {
        cout << "operator=" << endl;
        //自赋值判断
        if(this != &rhs)
        {
            //清理旧空间
            delete []_pstr;
            _pstr = nullptr;
            //深拷贝
            _pstr = new char[strlen(rhs._pstr)+1]{};
            strcpy(_pstr,rhs._pstr);
        }
        return *this;
    }
	~String()
    {
        cout << "~String" << endl;
    }
	void print()
    {
        cout << _pstr << endl;
    }
    //一个String对象的内容追加到当前String对象的末尾
    String & append(const String & rhs)
    {
        char *p = new char[strlen(_pstr)+strlen(rhs._pstr)+1];
        strcpy(p,this->_pstr);
        strcat(p,rhs._pstr);
        cout << p << endl;
        return *this;
    }

    //将C风格字符串追加到当前String对象的末尾
    String & append(const char * pstr)
    {
        char *p = new char[strlen(_pstr)+strlen(pstr)+1];
        strcpy(p,this->_pstr);
        strcat(p,pstr);
        cout << p << endl;
        return *this;

    }
    //返回字符串的长度（不包括结尾的空字符）
    size_t length() const
    {
        cout << strlen(this->_pstr)<< endl;
        return strlen(this->_pstr);
    }
    //返回C风格字符串的指针
    const char * c_str() const
    {
        return _pstr;
    }
private:
	char * _pstr;
};

int main()
{
	String str1;
	str1.print();
	

	String str2 = "Hello,world";
	String str3("wangdao");
	
	str2.print();		
	str3.print();	
	
	String str4 = str3;
	str4.print();
	
	str4 = str2;
	str4.print();
	cout << "------------"<< endl;
    str2.append(str3);
	cout << "------------"<< endl;
    str2.append("OK");
	cout << "------------"<< endl;
    str2.length();
	cout << "------------"<< endl;
    str2.c_str();
    printf("%s\n",str2.c_str());
	return 0;
}
