#include <iostream>
#include <memory>
// #include "WierdoTable.h"

int main()
{
    std::string word = "Hello world";

    std::cout << static_cast<int>(word.size());

    return 0;
}