#include "Mylogger.h"
void test()
{
    LogInfo("This is an info message");
    LogWarn("This is an warning message");
    LogError("This is an error message");
}
int main()
{
    test();
    Mylogger::destroyInstance();
    return 0;
}
