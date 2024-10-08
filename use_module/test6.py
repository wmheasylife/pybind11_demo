import sys
import os

import pickle

import numpy as np


build_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '../build'))

sys.path.insert(0, build_dir)

import dict_example

# 创建一个 Python 字典
my_dict = {
    "existing_key": "original_value",
    "another_key": 42
}

# 打印原始字典
print("Original dict:", my_dict)

# 调用 C++ 函数修改字典
dict_example.modify_dict(my_dict)

# 打印修改后的字典
print("Modified dict:", my_dict)

dict2 = None
dict_example.modify_dict(dict2)
print("Modified dict:", dict2)




# 创建一个 NumPy 数组
data = np.array([1.0, 2.0, 3.0, 4.0])

print("Original Data:", data)

# 调用 C++ 函数处理数组
dict_example.process_array(data)
print("process Data:", data)

dict_example.modify_array(data)

print("modify Data:", data)


data1 = dict_example.append_to_array(data)
print("append data :", data1)


o_dict = dict()
dict_example.modify_dict_array(o_dict)

print(o_dict)



# 
# 使用关键字参数调用函数
result = dict_example.contains_string(py_list=["apple", "banana", "cherry"], target="banana")
print(result)  # 输出: True

result = dict_example.contains_string(py_list=["apple", "banana", "cherry"], target="grape")
print(result)  # 输出: False


dict_example.create_dataframe()
