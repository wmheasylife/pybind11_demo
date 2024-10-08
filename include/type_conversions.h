#pragma once

#include <iostream>

#include <pybind11/pybind11.h>

namespace py = pybind11;

// void print_list(py::list my_list) {
//     for (auto item : my_list)
//         std::cout << item << " ";
// }

void print_dict(const py::dict& dict) {
    /* Easily interact with Python types */
    for (auto item : dict)
        std::cout << "key=" << std::string(py::str(item.first)) << ", "
                  << "value=" << std::string(py::str(item.second)) << std::endl;
}
// 


py::list create_list() {
    py::list list;
    list.append(1);
    list.append(2);
    list.append(3);
    return list;
}


py::list manipulate_list(const py::list& input_list) {
    py::list result;
    for (auto item : input_list) {
        // 假设我们要将每个元素乘以 2
        result.append(item.cast<int>() * 2);
    }
    return result;
}


void utf8_test(const std::string &s) {
    std::cout << "utf-8 is icing on the cake.\n";
    std::cout << s << std::endl;
}

void utf8_charptr(const char *s) {
    std::cout << "My favorite food is\n";
    std::cout << s << std::endl;
}


