#include "main.h"

int main()
{
    Test mainTest("SCIPP TEST", [](Test& test)->std::string {
        test.addSubTest("TEST DES ENTIERS", &mainInt);
        return "";
    });

    mainTest(0, 3);

    std::cout << std::endl;

    #ifdef SCP_TEST_PAUSE
    system("pause");
    #endif

    return 0;
}