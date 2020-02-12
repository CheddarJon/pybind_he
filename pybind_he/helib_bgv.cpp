#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <helib/helib.h>
#include <iostream>

PYBIND11_MAKE_OPAQUE(std::vector<long>);

namespace py = pybind11;

using CTX = helib::Context;
using PAA = helib::PAlgebra;
using SK  = helib::SecKey;
using PK  = helib::PubKey;
using EA  = helib::EncryptedArray;
using CT  = helib::Ctxt;

PYBIND11_MODULE(helib_bgv, m)
{
    py::class_<CTX>(m, "Context")
        .def(py::init([](unsigned long m, unsigned long p, unsigned long r) {
            return new CTX(m, p, r);
        }))
        .def_readwrite("zMStar", &CTX::zMStar)
        .def("printout", [](CTX& ctx) {
            py::scoped_ostream_redirect stream(
                std::cout,
                py::module::import("sys").attr("stdout")
            );
            ctx.zMStar.printout();
        })
        .def_readwrite("ea", &CTX::ea)
        .def("get_ea", [](CTX& ctx) { return *(ctx.ea); })
        .def("securityLevel", [](CTX& ctx) {
            return ctx.securityLevel();
        })
        ;

    py::class_<PAA>(m, "PAlgebra")
        .def(py::init<PAA>())
        .def("printout", [](PAA& p) { p.printout(); })
        ;

    py::class_<PK>(m, "PubKey")
        .def(py::init([](SK& sk) {
            return sk;
        }))
        ;

    py::class_<SK, PK>(m, "SecKey")
        .def(py::init([](CTX& ctx) {
            return new SK(ctx);
        }))
        .def("genSecKey", [](SK& sk) {
            sk.GenSecKey();
        })
        ;

    py::class_<std::vector<long>>(m, "VectorLong")
        .def(py::init<long>())
        .def("clear", &std::vector<long>::clear)
        .def("pop_back", &std::vector<long>::pop_back)
        .def("insert", [](std::vector<long> &v, long i, long val) {
            v[i] = val;
        })
        .def("__len__", [](const std::vector<long> &v) { return v.size(); })
        .def("__iter__", [](std::vector<long> &v) {
            return py::make_iterator(v.begin(), v.end());
        },  py::keep_alive<0, 1>()) /* Keep vector alive while iterator is used. */
        ;

    py::class_<EA>(m, "EncryptedArray")
        .def(py::init<EA>())
        .def("__len__", [](EA& ea) { return ea.size(); })
        .def("encrypt", [](EA& ea, CT& c, PK& pk, std::vector<long> &m) {
            ea.encrypt(c, pk, m);
        })
        .def("decrypt", [](EA& ea, CT& c, SK& sk, std::vector<long> &m) {
            ea.decrypt(c, sk, m);
        })
        ;

    py::class_<CT>(m, "Ctxt")
        .def(py::init([](PK& pk) {
            return new CT(pk);
        }))
        .def("Mul", [] (CT& c1, CT& c2) {
            c1 *= c2;
        })
        .def("Add", [] (CT& c1, CT& c2) {
            c1 += c2;
        })
        ;

    m.def("buildModChain", &helib::buildModChain,
        py::arg("context"), py::arg("bits"), py::arg("c") = 3,
        py::arg("willBeBootstrappable") = false,
        py::arg("skHwt") = 0, py::arg("resolution") = 3,
        py::arg("bitsInSpecialPrimes") = 0)
        ;
    m.def("addSome1DMatrices", [](SK& sk) {
            helib::addSome1DMatrices(sk);
        })
        ;
    m.def("vecToStr", [](std::vector<long> &v) {
            return helib::vecToStr(v);
        })
        ;
}
