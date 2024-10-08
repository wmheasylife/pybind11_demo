#include <pybind11/pybind11.h>

#include "bind_class.h"

namespace py = pybind11;


PYBIND11_MODULE(class_example, m) {
    py::class_<Animal, PyAnimal /* <--- trampoline*/>(m, "Animal")
        .def(py::init<>())
        .def("go", &Animal::go);

    py::class_<Dog, Animal>(m, "Dog")
        .def(py::init<>());


    m.def("call_go", &call_go);


}
