cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

## Use -std=c++14 as default.
set(CMAKE_CXX_STANDARD 14)
## Disable C++ extensions
set(CMAKE_CXX_EXTENSIONS OFF)
## Require full C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(helib_test
       	LANGUAGES CXX)

find_package(helib 1.0.0 EXACT REQUIRED)

set(SOURCES bgv_matrix_op.cpp BGV_general_example.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${helib_test_SOURCE_DIR}/bin)

foreach(f ${SOURCES})
    STRING(REPLACE ".cpp" "" fn ${f})
    add_executable(${fn} ${f})
    target_link_libraries(${fn} helib)
endforeach(f ${SOURCES})
