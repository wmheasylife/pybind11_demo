#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <iostream>

namespace py = pybind11;

// numpy::array 如果有多列，一列中的数据类型相同，不同列数据类型不同，在C++ 中访问和修改这个numpy::array

void modify_structured_array(py::array array) {
    // 获取数组的数据类型描述符
    auto dtype = array.dtype();
    auto fields = dtype.attr("fields");

    // 获取字段偏移量和数据类型
    auto int_info = fields["integers"].cast<std::pair<py::dtype, size_t>>();
    auto float_info = fields["floats"].cast<std::pair<py::dtype, size_t>>();

    size_t int_offset = int_info.second;
    size_t float_offset = float_info.second;

    // 获取数组的数据指针
    auto buf = array.request();
    char *data = static_cast<char *>(buf.ptr);

    size_t n = buf.shape[0]; // 数组中的元素个数

    for (size_t i = 0; i < n; ++i) {
        // 访问并修改字段 'integers' 和 'floats'
        int& int_value = *reinterpret_cast<int *>(data + i * buf.strides[0] + int_offset);
        double& float_value = *reinterpret_cast<double *>(data + i * buf.strides[0] + float_offset);

        // 修改数据
        int_value += 10;  // 例如，将整数字段加10
        float_value *= 2.0;  // 将浮点字段乘以2
    }
}


// numpy::array 如果有多列，一列中的数据类型相同，不同列数据类型不同，在C++ 中访问和修改这个numpy::array (添加列，并赋值)
void process_new_column_array(py::array array) {

    auto dtype = array.dtype();
    auto fields = dtype.attr("fields");

    // 访问新字段
    auto new_col_info = fields["new_column"].cast<std::pair<py::dtype, size_t>>();

    size_t new_col_offset = new_col_info.second;
    auto buf = array.request();
    char* data = static_cast<char*>(buf.ptr);

    size_t n = buf.shape[0];

    for (size_t i = 0; i < n; ++i) {
        // 访问并打印新列的值
        double& new_col_value = *reinterpret_cast<double*>(data + i * buf.strides[0] + new_col_offset);
        std::cout << "New column value: " << new_col_value << std::endl;
        // 可以在这里对新列进行其他处理
        new_col_value = 1949.101 * i;
    }

}


py::object create_structured_array(size_t num_rows) {
    // 通过 Python 构造 dtype
    py::object numpy = py::module_::import("numpy");
    py::object dtype = numpy.attr("dtype");
    py::object structured_dtype = dtype(py::make_tuple(
        py::make_tuple("col1", "float64"),
        py::make_tuple("col2", "float32"),
        py::make_tuple("col3", "float64")
    ));

    // 创建空数组
    py::array result = numpy.attr("empty")(py::make_tuple(num_rows,), structured_dtype);

    // 填充数据
    for (size_t i = 0; i < num_rows; ++i) {
        result.mutable_at(i).attr("setfield")(static_cast<double>(i), "f8", 0);
        result.mutable_at(i).attr("setfield")(static_cast<float>(i), "f4", 8);
        result.mutable_at(i).attr("setfield")(static_cast<double>(i), "f8", 12);
    }

    return result;
}


