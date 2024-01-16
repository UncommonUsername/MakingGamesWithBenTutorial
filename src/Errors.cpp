#include "Errors.h"

#include <iostream>

extern void fatalError(std::string errorMessage)
{
    std::cout << errorMessage << std::endl;
    std::cout << "Enter any key to quit...\n";
    int tmp;
    std::cin >> tmp;
    exit(EXIT_FAILURE);
}