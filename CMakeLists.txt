cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(pybind_he)

find_package(PythonLibs)
include_directories(${PYTHON_INCLUDE_DIRS})

add_subdirectory(submodules/Pybind)


#set(PACKAGE_BUILD ON)
#add_subdirectory(submodules/HElib)
find_package(helib 1.0.0 EXACT REQUIRED)

set(SOURCES pybind_he/pybind_he.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)


foreach(f ${SOURCES})
	get_filename_component(base_name ${f} NAME)
    STRING(REPLACE ".cpp" "bin" fn ${base_name})
    add_executable(${fn} ${f})
    target_link_libraries(${fn} PRIVATE helib)
endforeach(f ${SOURCES})

pybind11_add_module(pybind_he pybind_he/pybind_he.cpp)