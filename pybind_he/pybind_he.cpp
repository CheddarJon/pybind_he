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
		.def(py::init([](unsigned long m, unsigned long p, unsigned long r) {
			return new CTX(m, p, r);
        }))
        .def_readwrite("zMStar", &CTX::zMStar)
        /*.def("printout", [](CTX& ctx) {
            py::scoped_ostream_redirect stream(
                std::cout,
                py::module::import("sys").attr("stdout")
            );
            ctx.zMStar.printout();
        })*/
        .def_readwrite("ea", &CTX::ea)
        .def("get_ea", [](CTX& ctx) { return *(ctx.ea); })
        .def("securityLevel", [](CTX& ctx) {
            return ctx.securityLevel();
        });
}
#endif

#ifdef BARE_BONE
#pragma message ( "RUNNING BARE BONE" )
void Breaker(void) {}

int main(int argc, char *argv[])
{
    PrintContext();
	Breaker();
}
#endif
