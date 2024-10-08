#include <pybind11/pybind11.h>

#include "bind_class_2.h"
#include "custom_constructors.h"

namespace py = pybind11;


PYBIND11_MODULE(class_example2, m) {
    py::class_<Animal, PyAnimal<>> animal(m, "Animal");
    animal.def(py::init<>());
    py::class_<Dog, Animal, PyDog<>> dog(m, "Dog");
    dog.def(py::init<>());
    py::class_<Husky, Dog, PyDog<Husky>> husky(m, "Husky");
    husky.def(py::init<>());


    m.def("call_go", &call_go);


    // py::class_<Example>(m, "Example")
    //     // Bind the factory function as a constructor:
    //     .def(py::init(&Example::create))
    //     // Bind a lambda function returning a pointer wrapped in a holder:
    //     .def(py::init([](std::string arg) {
    //         return std::unique_ptr<Example>(new Example(arg));
    //     }))
    //     // Return a raw pointer:
    //     .def(py::init([](int a, int b) { return new Example(a, b); }))
    //     // You can mix the above with regular C++ constructor bindings as well:
    //     .def(py::init<double>())
    //     ;


    py::class_<Aggregate>(m, "Aggregate")
        .def(py::init<int, const std::string &>())
        .def_readwrite("a", &Aggregate::a)
        .def_readwrite("b", &Aggregate::b);

}




