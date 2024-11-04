import sys
import os
import pandas as pd
import numpy as np

build_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '../build'))

sys.path.insert(0, build_dir)

import numpy_example

# 创建一个结构化数组
dtype = np.dtype([('integers', np.int32), ('floats', np.float64)])
data = np.array([(1, 2.0), (3, 4.0), (5, 6.0)], dtype=dtype)

print("Before modification:")
print(data)


# 调用C++函数来修改数组
numpy_example.modify_structured_array(data)

print("After modification:")
print(data)






print("-" * 40)


# 创建一个初始的结构化数组
dtype = np.dtype([('integers', np.int32), ('floats', np.float64)])
data = np.array([(1, 2.0), (3, 4.0), (5, 6.0)], dtype=dtype)

print("Original array:")
print(data)

# 定义新列的dtype
new_dtype = np.dtype(data.dtype.descr + [('new_column', np.float64)])

# 创建一个新的结构化数组
new_data = np.zeros(data.shape, dtype=new_dtype)


# 将旧数据复制到新数组中
for name in data.dtype.names:
    new_data[name] = data[name]


# 初始化新列数据
new_data['new_column'] = [10.0, 20.0, 30.0]

print("Array after adding new column:")
print(new_data)

