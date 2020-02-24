#include <pybind11/pybind11.h>

/*
	The pybind_he will be THE module that enables already identified HElib
	cXX-functions for optimization into your everyday python. 
	
	For installing the below functionality, run the setup and in python
	import <WRITE-MODULE-NAME>
*/

int add(int i, int j) {
    return i + j;
}

PYBIND11_MODULE(pybind_he, m) {
    m.doc() = "Pybind_he blabla"; 

    m.def("add", &add, "A function which adds two numbers");
}