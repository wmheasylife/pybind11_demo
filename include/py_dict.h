#pragma once

#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <string>
#include <thread>
#include <pybind11/embed.h> // 这里用于嵌入 Python 解释器

namespace py = pybind11;

void modify_dict(py::object & d) {
   if (d.is_none()) {
        py::print("Received None, nothing to modify.");
        return;
    }


    // 向字典中添加一个新的键值对
    d["new_key"] = "new_value";


    // 修改已有的键值对
    if (d.contains("existing_key")) {
        d["existing_key"] = "modified_value";
    }
}


void process_array(py::array_t<double> array) {

    // 检查数组是否为连续内存块
    py::buffer_info buf = array.request();

    if (buf.ndim != 1) {
        throw std::runtime_error("Number of dimensions must be one");
    }

    // 获取指向数组数据的指针
    double *ptr = static_cast<double *>(buf.ptr);

    // 处理数组数据
    for (size_t idx = 0; idx < buf.shape[0]; idx++) {
        std::cout << ptr[idx] << std::endl;
    }
}


void modify_array(py::array_t<double> array) {

    // 检查数组是否为连续内存块
    py::buffer_info buf = array.request();

    if (buf.ndim != 1) {
        throw std::runtime_error("Number of dimensions must be one");
    }

    // 获取指向数组数据的指针
    double *ptr = static_cast<double *>(buf.ptr);

    // 修改数组数据
    for (size_t idx = 0; idx < buf.shape[0]; idx++) {
        ptr[idx] *= 2;  // 将每个元素乘以 2
    }

}




// 这个函数接收一个数组，并返回一个增加了元素的新数组
py::array_t<double> append_to_array(py::array_t<double> array) {
    // 获取输入数组的信息
    py::buffer_info buf = array.request();

    if (buf.ndim != 1) {
        throw std::runtime_error("Number of dimensions must be one");
    }

    // 获取输入数组的大小
    size_t original_size = buf.shape[0];

    // 创建一个新的数组，其大小比原数组多一个元素
    py::array_t<double> result(original_size + 1);

    // 获取新数组的信息
    py::buffer_info result_buf = result.request();

    // 将原数组的数据复制到新数组中
    double *ptr = static_cast<double *>(buf.ptr);
    double *result_ptr = static_cast<double *>(result_buf.ptr);

    for (size_t idx = 0; idx < original_size; idx++) {
        result_ptr[idx] = ptr[idx];
    }

    // 添加新的元素到新数组的末尾
    result_ptr[original_size] = 100.0;

    return result;
}


void modify_dict_array(py::dict& d) {

    size_t arr_size = 100;
    py::array_t<double> float_result(arr_size);
    py::buffer_info buf = float_result.request();
    double *ptr = static_cast<double *>(buf.ptr);
    for (size_t i = 0; i < arr_size; ++i) {
        ptr[i] = i * 1.0;
    }
    d["float"] = float_result;

    py::array_t<int> int_result(arr_size);
    py::buffer_info buf1 = int_result.request();
    int *ptr1 = static_cast<int *>(buf1.ptr);
    for (size_t i = 0; i < arr_size; ++i) {
        ptr1[i] = i * 2;
    }
    d["int"] = int_result;

    std::vector<std::string> stl_str_vec;
    for (size_t i = 0; i < arr_size; ++i) {
        stl_str_vec.push_back(std::to_string(i) + "_std_string");
    }
    py::list temp_py_list;
    for (const auto& str : stl_str_vec) {
        temp_py_list.append(py::str(str));  // 将 std::string 转换为 py::str 并附加到 py_list
    }

    // // 将列表转换为 numpy 数组
    // py::array_t<py::object> py_array(py_list.size());
    // for (size_t i = 0; i < py_list.size(); ++i) {
    //     py_array.mutable_at(i) = py_list[i];
    // }

    d["str"] = temp_py_list;

    py::array_t<uint64_t> uint64_result(arr_size);
    d["uint64"] = uint64_result;
    py::array_t<uint64_t> col_numpy4 = py::cast<py::array>(d["uint64"]);
    py::buffer_info buf4 = col_numpy4.request();
    uint64_t *ptr4 = static_cast<uint64_t *>(buf4.ptr);
    for (size_t i = 0; i < arr_size; ++i) {
        ptr4[i] = i * 10;
    }



    // 启动一个子线程，使用 lambda 表达式捕获 myVector
    py::array_t<uint64_t> col_numpy5(arr_size);
    py::buffer_info buf5 = col_numpy5.request();
    uint64_t *ptr5 = static_cast<uint64_t *>(buf5.ptr);

    d["sub_uint64"] = col_numpy5;
    std::thread workerThread([&arr_size, &ptr5]() {
        for (size_t i = 0; i < arr_size; ++i) {
            ptr5[i] = i * 15;
        }
    });


    std::map<std::string, void *> stl_map_pointer;
    py::array_t<uint64_t> col_numpy6(arr_size);
    py::buffer_info buf6 = col_numpy6.request();
    d["sub_uint64_1"] = col_numpy6;
    uint64_t *ptr6 = static_cast<uint64_t *>(buf6.ptr);
    std::cout << "1 ptr6 pointer: " << ptr6 << std::endl;
    // for (size_t i = 0; i < arr_size; ++i) {
    //     std::cout << "1-1 ptr6 pointer: " << ptr6 << std::endl;
    //     ptr6[i] = i * 640;
    // }
    std::cout << "2 ptr6 pointer: " << ptr6 << std::endl;
    stl_map_pointer["sub_uint64_1"] = static_cast<void *>(buf6.ptr);
    std::cout << "3 ptr6 pointer: " << ptr6 << std::endl;
    std::cout << "ptr6 pointer: " << ptr6 << ", stl_map_pointer[sub_uint64_1]" << (static_cast<uint64_t *>(stl_map_pointer["sub_uint64_1"])) << std::endl;
    for (size_t i = 0; i < arr_size; ++i) {
        std::cout << "3-1 ptr6 pointer: " << ptr6 << "*ptr[i]:" << &ptr6[i]<< std::endl;
        std::cout << ptr6[i] << std::endl;
    }

    py::array_t<uint32_t> col_numpy7(arr_size);
    py::buffer_info buf7 = col_numpy7.request();
    d["sub_uint32_1"] = col_numpy7;
    uint32_t *ptr7 = static_cast<uint32_t *>(buf7.ptr);
    stl_map_pointer["sub_uint32_1"] = static_cast<void *>(buf7.ptr);


    std::thread workerThread1([&arr_size, &stl_map_pointer]() {
        void* ptr6 = stl_map_pointer["sub_uint64_1"];
        uint64_t *ptr6_1 = static_cast<uint64_t *>(ptr6);
        std::cout << "4 ptr6_1 pointer: " << ptr6_1 << std::endl;
        for (size_t i = 0; i < arr_size; ++i) {
            std::cout << "4-1 ptr6 pointer: " << ptr6_1 << "*ptr[i]:" << &ptr6_1[i]<< std::endl;
            ptr6_1[i] = i * 64 + 3;
        }
        void* ptr7 = stl_map_pointer["sub_uint32_1"];
        uint32_t *ptr7_1 = static_cast<uint32_t *>(ptr7);
        std::cout << "4 ptr7_1 pointer: " << ptr7_1 << std::endl;
        for (size_t i = 0; i < arr_size; ++i) {
            std::cout << "4-1 ptr6 pointer: " << ptr7_1 << "*ptr[i]:" << &ptr7_1[i]<< std::endl;
            ptr7_1[i] = i * 64 + 4;
        }
    });

    // // 等待子线程完成

    workerThread.join();
    workerThread1.join();


}


// 传递一个python list 过来，在C++判断某个字符串是否存在。
bool contains_string(const py::list& py_list, const std::string& target) {
    for (auto item : py_list) {
        if (py::isinstance<py::str>(item)) {  // 检查元素是否是字符串
            std::string str = item.cast<std::string>();
            if (str == target) {
                return true;
            }
        }
    }
    return false;

}




void create_dataframe() {
    // 导入 pandas 模块
    py::module_ pandas = py::module_::import("pandas");

    // 创建一个简单的 DataFrame
    py::dict data;
    data["A"] = py::make_tuple(1, 2, 3);
    data["B"] = py::make_tuple(4, 5, 6);

    // 调用 pandas.DataFrame 构造函数
    py::object df = pandas.attr("DataFrame")(data);

    // 打印 DataFrame
    py::print(df);
}


