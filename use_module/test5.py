import sys
import os

import pickle


build_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '../build'))

sys.path.insert(0, build_dir)

import type_example

# 创建一个列表
lst = type_example.create_list()
print(lst)  # 输出: [1, 2, 3]

# 操作列表
new_lst = type_example.manipulate_list(lst)
print(new_lst)  # 输出: [2, 4, 6]
print(type(new_lst))

cus_list = [10, 30, 50]
newest_lst = type_example.manipulate_list(cus_list)
print(newest_lst)
print(type(newest_lst))



type_example.utf8_test("🎂")

type_example.utf8_charptr("🍕")

# 输出True
print(isinstance(type_example.std_string_return(), str))