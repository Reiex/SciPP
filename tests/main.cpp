#include "main.h"

int main()
{
    Test mainTest("TESTS OF THE LIBRARY SCIPP", [](Test& test)->std::string {
        test.addSubTest("INTEGERS", &mainInt);
        return "";
    });

    mainTest(0, 3);

    std::cout << std::endl;

    #ifdef SCP_TEST_PAUSE
    system("pause");
    #endif

    return 0;
}