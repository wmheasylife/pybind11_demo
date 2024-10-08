#include <pybind11/pybind11.h>

#include "py_dict.h"

namespace py = pybind11;


PYBIND11_MODULE(dict_example, m) {
    m.def("modify_dict", &modify_dict, "Modify a Python dictionary");
    m.def("process_array", &process_array, "Process a NumPy array");
    m.def("modify_array", &modify_array, "Modify a NumPy array");
    m.def("append_to_array", &append_to_array, "append to a NumPy array");
    m.def("modify_dict_array", &modify_dict_array, "modify python dict with value as NumPy array");
    m.def("contains_string", &contains_string, py::arg("py_list"), py::arg("target"), 
                                "Check if a list contains a specific string");
    m.def("create_dataframe", &create_dataframe, "Modify a NumPy array");
}
