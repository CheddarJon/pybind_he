#include "pybind_he.h"

/*
	The pybind_he will be THE module that enables already identified HElib
	cXX-functions for optimization into your everyday python.

	For installing the below functionality, run the setup and in python
	import <WRITE-MODULE-NAME>
*/



#ifndef BARE_BONE
PYBIND11_MODULE(pybind_he, m)
{
    m.doc() = "IM ALIVE";

    m.def("john", &john_helib, "Example of BGV scheme");
}
#endif

#ifdef BARE_BONE
#pragma message ( "RUNNING BARE BONE" )
int main(int argc, char *argv[])
{
    john_helib();
}
#endif
