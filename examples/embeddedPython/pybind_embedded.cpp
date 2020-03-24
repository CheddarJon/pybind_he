#include <pybind11/embed.h>
#include <iostream>
namespace py = pybind11;

void MockFFT(int flag) {
    if (flag == 1) {
        // Run python version
        py::scoped_interpreter guard{};

        py::module fft = py::module::import("MockFPGA");
        py::object result = fft.attr("execute")(2, 4);
        int n = result.cast<int>();
        assert(n == 8);
    } else {
        // Run c++ version
        std::cout << "Running fft implemented in c++" << std::endl;
    }
}

int main() {
    MockFFT(1);
    MockFFT(0);
}
