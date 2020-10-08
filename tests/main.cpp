#include "main.h"

void printSection(const std::string& testName, const std::string& sectionName)
{
    std::cout << "\e[0;33m[ SECTION  ]\e[0m " << testName << ": " << sectionName << std::endl;
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}