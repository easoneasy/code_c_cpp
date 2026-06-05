#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Record
{
	string _word;
	int _frequency;
};

class Dictionary
{
public:
    void read(const std::string &filename);
    void store(const std::string &filename);
private:
    vector<Record> _dict;
};
void test1(){

}

int main(int argc,char *argv[])
{
    test1();

    return 0;
}

