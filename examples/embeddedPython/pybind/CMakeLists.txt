cmake_minimum_required(VERSION 3.0)
project(pybind_interpreter)

find_package(pybind11 REQUIRED)

add_executable(pb_int pybind_embedded.cpp)
target_link_libraries(pb_int PRIVATE pybind11::embed)
