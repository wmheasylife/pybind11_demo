import sys
import os

build_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '../build'))

sys.path.insert(0, build_dir)

import class_example2 as ce


d = ce.Dog()
d_o = ce.call_go(d)
print(d_o)


class Cat(ce.Animal):
    def __init__(self, name):
        ce.Animal.__init__(self); # without this TypeError is raised
        self.name = name

    def go(self, n_times):
        return "meow! " * n_times


c = Cat("your name")
c_o = ce.call_go(c)
print(c_o)


class WangCai(ce.Dog):
    def __init__(self, name):
        ce.Dog.__init__(self)
        self.name = name

    def go(self, n_times):
        return "WangCai_go! " * n_times

    def bark(self):
        return f"{self.name}_wang" * 10


w_cai = WangCai('WangCai')

print(w_cai.go(5))
print(w_cai.bark())



# example_ins = ce.Example()

# print(example_ins)


aggregate_ins = ce.Aggregate(10, 'abc')
print(aggregate_ins)

print(aggregate_ins.a)
print(aggregate_ins.b)


