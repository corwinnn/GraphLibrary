#include <iostream>

#include "Examples/GraphExample.h"
#include "Examples/SingleTypeGraphExample.h"
#include "Examples/ChainResponsibility.h"
#include "Examples/StringEdges.h"

int main() {
    graphExample();
    std::cout << "\n\n\n";
    singleTypeGraphExample();
    std::cout << "\n\n\n";
    chainResponsibility();
    std::cout << "\n\n\n";
    stringEdges();
    std::cout << "\n\n\n";
}
