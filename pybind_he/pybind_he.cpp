#include "pybind_he.h"

/*
	The pybind_he will be THE module that enables already identified HElib
	cXX-functions for optimization into your everyday python.

	For installing the below functionality, run the setup and in python
	import <WRITE-MODULE-NAME>
*/

using CTX = helib::Context;

#ifndef BARE_BONE
PYBIND11_MODULE(pybind_he, m)
{
    m.doc() = "IM ALIVE";

    m.def("PrintContext", &PrintContext, "Prints Stuff from Context");

	// ----------------
	// From HElib with love
	// ----------------

	py::class_<CTX>(m, "Context")
		// Return a raw pointer:
		.def(py::init([](unsigned long m, unsigned long p, unsigned long r) { return new CTX(m, p, r);}));
}
#endif

#ifdef BARE_BONE
#pragma message ( "RUNNING BARE BONE" )
int main(int argc, char *argv[])
{
    PrintContext();
}
#endif
