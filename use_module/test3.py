import sys
import os

import pickle


build_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '../build'))

sys.path.insert(0, build_dir)

import op_example as oe


p = oe.Pickleable('test_value')
p.setExtra(15)
data = pickle.dumps(p)
print(data)