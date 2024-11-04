#include <pybind11/pybind11.h>

#include "numpy_array.h"

namespace py = pybind11;


#include <pybind11/operators.h>

PYBIND11_MODULE(numpy_example, m) {
    m.def("modify_structured_array", &modify_structured_array, "Modify a structured NumPy array in place");
    m.def("process_new_column_array", &process_new_column_array, "Process a NumPy structured array with a new column");
    m.def("create_structured_array", &create_structured_array, "Create a structured array with mixed types in columns");
}