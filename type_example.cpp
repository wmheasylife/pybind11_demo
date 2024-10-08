#include <pybind11/pybind11.h>

#include "type_conversions.h"

namespace py = pybind11;


PYBIND11_MODULE(type_example, m) {
    m.def("create_list", &create_list, "Create a Python list with elements 1, 2, 3");
    m.def("manipulate_list", &manipulate_list, "Multiply each element in the list by 2");

    m.def("utf8_test", utf8_test);
    m.def("utf8_charptr", utf8_charptr);

    m.def("std_string_return",
        []() {
            return std::string("This string needs to be UTF-8 encoded");
        }
    );


    // This uses the Python C API to convert Latin-1 to Unicode
    m.def("explicit_str_output",
        []() {
            std::string s = "Send your 名称 to Alice in HR"; // Latin-1
            return s;
            // py::handle py_s = PyUnicode_DecodeLatin1(s.data(), s.length(), nullptr);
            // if (!py_s) {
            //     throw py::error_already_set();
            // }
            // return py::reinterpret_steal<py::str>(py_s);
        }
    );


}
