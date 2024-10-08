import sys
import os

build_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '../build'))

sys.path.insert(0, build_dir)

import class_example as ce


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





