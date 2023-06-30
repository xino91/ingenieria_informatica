cmake_minimum_required (VERSION 3.1)
project (graphs)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
add_executable(test test.cpp graph.hpp graph_utils.hpp city.hpp city.cpp)
