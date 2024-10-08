cmake_minimum_required(VERSION 3.10)
project(wmh_example)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(pybind11)
# add_subdirectory(sub)  # does not contain a CMakeLists.txt file


file(GLOB SUB_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
include_directories(${CMAKE_SOURCE_DIR}/include)

pybind11_add_module(wmh_example wmh_example.cpp ${SUB_FILES})
pybind11_add_module(class_example class_example.cpp ${SUB_FILES})
pybind11_add_module(class_example2 class_example2.cpp ${SUB_FILES})

pybind11_add_module(op_example op_example.cpp ${SUB_FILES})
pybind11_add_module(smart_pointer_example smart_pointer.cpp ${SUB_FILES})


pybind11_add_module(type_example type_example.cpp ${SUB_FILES})

pybind11_add_module(dict_example dict_example.cpp ${SUB_FILES})



