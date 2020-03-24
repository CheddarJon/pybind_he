#include <pybind11/embed.h>
#include <iostream>
#include <stdlib.h>

namespace py = pybind11;

void
MockFFT(int a, int b)
{
    char *overlay;
    // It should be set to the name of the python script (no extension)
    // The script needs to be located in the current directory or in PYTHONPATH
    overlay = getenv("PYTHON_OVERLAY");

    if (overlay != NULL) {
        // Run python version
        py::scoped_interpreter guard{};

        py::module fft = py::module::import(overlay);
        py::object result = fft.attr("execute")(a, b);
        int n = result.cast<int>();
        assert(n == 8);
        std::cout << a << " * " << b << " = " << n << std::endl;
    } else {
        // Run c++ version
        std::cout << "Running fft implemented in c++" << std::endl;
        std::cout << a << " * " << b << " = " << a*b << std::endl;
    }
}

int
main()
{
    MockFFT(2, 4);

    return 0;
}
