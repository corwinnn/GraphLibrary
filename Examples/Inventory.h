#pragma once

#include "../Graph.h"
#include <iostream>
#include <memory>
#include <string>

struct A{
    A(int x): x(x){};
    void foo(int a) {
        std::cout << "I'm A with x, a:" << std::to_string(x) << " " << std::to_string(a) << std::endl;
    }
    int x;
};
struct B{};
struct C{};
struct D{};
