#include "Errors.h"

#include <iostream>
#include <cstdlib>

extern void fatalError(std::string errorMessage)
{
    std::cout << errorMessage << std::endl;
    std::cout << "Enter any key to quit...\n";
    int tmp;
    std::cin >> tmp;
    exit(69);
}