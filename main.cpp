#include <iostream>

#include "Examples/DifferentTypeGraph.h"
#include "Examples/SingleTypeGraph.h"
#include "Examples/ChainResponsibility.h"
#include "Examples/StringEdges.h"
#include "Examples/CompositePattern.h"

int main() {
    graphExample();
    std::cout << "\n\n\n";
    singleTypeGraphExample();
    std::cout << "\n\n\n";
    chainResponsibility();
    std::cout << "\n\n\n";
    stringEdges();
    std::cout << "\n\n\n";
    composite();
}
