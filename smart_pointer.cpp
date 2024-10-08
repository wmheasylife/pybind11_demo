#include <pybind11/pybind11.h>

#include "smart_pointer.h"

namespace py = pybind11;


PYBIND11_MODULE(smart_pointer_example, m) {

    py::class_<Pet, std::shared_ptr<Pet>>(m, "Pet")
        .def(py::init<const std::string &>())
        .def("setName", &Pet::setName)
        .def("getName", &Pet::getName);

}