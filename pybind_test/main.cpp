#include <pybind11/embed.h> // everything needed for embedding
namespace py = pybind11;

int tst(py::module overlay)
{
	py::object result = overlay.attr("add")(1, 2);
	int n = result.cast<int>();
	assert(n == 3);
	return n;
}

void tstbase(py::module overlay, py::object base)
{
	for (int i = 0; i < 10000; i++)
		overlay.attr("led")(base);
}

void wrap1(py::module overlay)
{
	overlay.attr("add")(5, 6);
}

int main() {
	char *overlay = getenv("PYTHONOVERLAY");
	if (overlay == NULL)
		return -1;
    	py::scoped_interpreter guard{}; // start the interpreter and keep it alive
	py::module mod = py::module::import(overlay);
	//py::module sys = py::module::import("sys");
	/*
        from pynq import PL
	from pynq.overlays.base import BaseOverlay

	base = BaseOverlay("base.bit")
	*/
	//py::module pynq = py::module::import("pynq");
	//py::module base = py::module::import("pynq.overlays.base");	
	
	//py::object basebit = pynq.attr("Overlay")("/home/xilinx/adder.bit");

	//calc.attr("add")(5, 6);
	
	
	wrap1(mod);
	wrap1(mod);
	//tstbase(calc, basebit);
	//py::print(n);
}
