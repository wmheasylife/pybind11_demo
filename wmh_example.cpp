#include <pybind11/pybind11.h>

#include "sample_function.h"
#include "custom_type.h"
#include "type_conversions.h"
#include "advance_function.h"

namespace py = pybind11;

PYBIND11_MODULE(wmh_example, m) {
    // bingding sample function
    m.doc() = "pybind11 example plugin"; // 可选的模块文档字符串
    m.def("add", &add, "A function which adds two integers");

    // regular notation
    m.def("add1", &add1, py::arg("i"), py::arg("j"));
    // shorthand
    using namespace pybind11::literals;
    m.def("add2", &add2, "i"_a, "j"_a);

    // Default arguments 默认参数
    m.def("add3", &add3, "A function which adds two numbers",
        py::arg("i") = 30, py::arg("j") = 100);
    // regular notation
    m.def("add4", &add4, py::arg("i") = 40, py::arg("j") = 100);
    // shorthand
    m.def("add5", &add5, "i"_a=50, "j"_a=100);

    // 扩展python module 属性
    m.attr("the_answer") = 42;
    py::object world = py::cast("World");
    m.attr("what") = world;



    // Object-oriented code
    // bind 用户自定义类型
    py::class_<Pet>(m, "Pet", py::dynamic_attr())   /* Dynamic attributes for C++ classes, the py::dynamic_attr tag must be added to the py::class_ constructor: */
        .def(py::init<const std::string &>())
        .def("setName", &Pet::setName)
        .def("getName", &Pet::getName)  // 这种定义方法，不能是 name字典在 python中直接使用，比如 pet_instance.name = ....,  
        .def("__repr__",            /* Binding lambda functions */ 
            [](const Pet &a) {
                return "<example.Pet named '" + a.getName() + "'>";
            }
        )  /*  通过这种bind, 在python 中print Pet 实例时，又 "<example.Pet object at 0x10cd98060>" 变成 "<example.Pet named 'Molly'>" */ 
        .def_readwrite("name", &Pet::name)  /*  这种方式可以使name 通过 pet_instance.name 直接访问  */
                                             /* 注意这里的name不能为private, 否则编译是报： error: ‘std::string Pet::name’ is private within this context */ 
        .def_property("first_name", &Pet::getFirstName, &Pet::setFirstName);   /* first_name为私有变量，这里一定要通过成员函数访问 */

    // Inheritance and automatic downcasting(继承和自动向下转型)
    // Method 1: template parameter:
    py::class_<Dog, Pet /* <- specify C++ parent type */>(m, "Dog")
        .def(py::init<const std::string &>())
        .def("bark", &Dog::bark);

    py::class_<Pet2> pet2(m, "Pet2");
    pet2.def(py::init<const std::string &>())
        .def_readwrite("name", &Pet2::name);
    // Method 2: pass parent class_ object:
    py::class_<Dog2>(m, "Dog2", pet2 /* <- specify Python parent type */)
        .def(py::init<const std::string &>())
        .def("bark", &Dog2::bark);


    // Same binding code
    py::class_<PolymorphicPet>(m, "PolymorphicPet");    /*  In C++, a type is only considered polymorphic if it has at least one virtual function and pybind11 will automatically recognize this: */
    py::class_<PolymorphicDog, PolymorphicPet>(m, "PolymorphicDog")
        .def(py::init<>())
        .def("bark", &PolymorphicDog::bark);
    m.def("pet_store2", []() { return std::unique_ptr<PolymorphicPet>(new PolymorphicDog); });

    // 函数重载bind
    //    If you have a C++14 compatible compiler [2], you can use an alternative syntax to cast the overloaded function:
    py::class_<Pet3>(m, "Pet3")
        .def(py::init<const std::string &, int>())
        .def("set", static_cast<void (Pet3::*)(int)>(&Pet3::set), "Set the pet3's age")
        .def("set", static_cast<void (Pet3::*)(const std::string &)>(&Pet3::set), "Set the pet3's name")
        .def("set_v2", py::overload_cast<int>(&Pet3::set_v2), "Set the pet's age")
        .def("set_v2", py::overload_cast<const std::string &>(&Pet3::set_v2), "Set the pet's name");

    // 函数重载 带有const 类型
    py::class_<Widget>(m, "Widget")
        .def("foo_mutable", py::overload_cast<int, float>(&Widget::foo))
        .def("foo_const",   py::overload_cast<int, float>(&Widget::foo, py::const_));


    py::class_<Pet4> pet4(m, "Pet4");

    pet4.def(py::init<const std::string &, Pet4::Kind>())
        .def_readwrite("name", &Pet4::name)
        .def_readwrite("type", &Pet4::type)
        .def_readwrite("attr", &Pet4::attr);

    py::enum_<Pet4::Kind>(pet4, "Kind")
        .value("Dog", Pet4::Kind::Dog)
        .value("Cat", Pet4::Kind::Cat)
        .export_values();

    py::class_<Pet4::Attributes>(pet4, "Attributes")
        .def(py::init<>())
        .def_readwrite("age", &Pet4::Attributes::age);




    // bind class static 函数
    py::class_<Math>(m, "Math")
        .def_static("add", &Math::add);

    // py::class_<Animal>(m, 'Animal')
    //     .def("go", &Animal::go);

    // py::class_<Dog, Animal>(m, "Dog");

    // m.def("call_go", &call_go);

    m.def("get_data", &get_data, py::return_value_policy::reference); // <-- KABOOM, will cause crash when called from Python
    m.def("print_dict", &print_dict);













}



