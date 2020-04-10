cmake_minimum_required(VERSION 3.0)
project(example)

find_package(pybind11 REQUIRED)  # or `add_subdirectory(pybind11)`
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
add_executable(tutorial tutorial.cpp)
add_executable(example main.cpp)
target_link_libraries(tutorial PRIVATE /usr/local/lib/libtfhe-fftw.so pybind11::embed)
target_link_libraries(example PRIVATE /usr/local/lib/libtfhe-fftw.so pybind11::embed)
