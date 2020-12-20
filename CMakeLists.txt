cmake_minimum_required(VERSION 3.15)
project(GraphLibrary)

set(CMAKE_CXX_STANDARD 20)

add_executable(GraphLibrary main.cpp Graph.h Examples/Inventory.h Examples/GraphExample.h Examples/SingleTypeGraphExample.h Examples/ChainResponsibility.h)