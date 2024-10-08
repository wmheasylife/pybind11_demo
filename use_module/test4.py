import sys
import os

import pickle


build_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '../build'))

sys.path.insert(0, build_dir)

import smart_pointer_example
# 创建一个 Pet 对象
pet = smart_pointer_example.Pet("Fluffy")
print(pet.getName())  # 输出: Fluffy

# 修改 Pet 对象的名称
pet.setName("Fido")
print(pet.getName())  # 输出: Fido


del pet # 这里 del 的时候，Pet 的析构函数

print('end')