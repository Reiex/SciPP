#include "main.h"

void printSection(const std::string& name)
{
    std::cout << "\e[0;32m[ SECTION  ]\e[0m " << name << std::endl;
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}