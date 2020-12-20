cmake_minimum_required(VERSION 3.15)
project(GraphLibrary)

set(CMAKE_CXX_STANDARD 20)

add_executable(GraphLibrary main.cpp Graph.h Examples/Inventory.h Examples/DifferentTypeGraph.h Examples/SingleTypeGraph.h Examples/ChainResponsibility.h Examples/StringEdges.h Examples/CompositePattern.h)