#include <iostream>
#include <pybind11/pybind11.h>
#include <helib/helib.h>

using namespace helib;
namespace py = pybind11;



int PrintContext() 
{
    unsigned long p = 4999;
    unsigned long m = 321090;
    unsigned long r = 1;
    
    std::cout << "Initialising context object..." << std::endl;
    
    Context context(m, p, r);

    return 0;
}