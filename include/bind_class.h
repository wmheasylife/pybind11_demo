#pragma once

#include <iostream>
#include <string>


class Animal {
public:
    virtual ~Animal() { }
    virtual std::string go(int n_times) = 0;
};

class Dog : public Animal {
public:
    std::string go(int n_times) override {
        std::string result;
        for (int i=0; i<n_times; ++i)
            result += "woof! ";
        return result;
    }
};

std::string call_go(Animal *animal) {
    return animal->go(3);
}



class PyAnimal : public Animal {
public:
    /* Inherit the constructors */
    using Animal::Animal;

    /* Trampoline (need one for each virtual function) */
    std::string go(int n_times) override {
        PYBIND11_OVERRIDE_PURE(
            std::string, /* Return type */
            Animal,      /* Parent class */
            go,          /* Name of function in C++ (must match Python name) */
            n_times      /* Argument(s) */
        );
    }
};


class Animal1 {
public:
    virtual std::string go(int n_times) = 0;
    virtual std::string name() { return "unknown"; }
};

class Dog1 : public Animal1 {
public:
    std::string go(int n_times) override {
        std::string result;
        for (int i=0; i<n_times; ++i)
            result += bark() + " ";
        return result;
    }
    virtual std::string bark() { return "woof!"; }
};


class PyAnimal1 : public Animal1 {
public:
    using Animal1::Animal1; // Inherit constructors
    std::string go(int n_times) override { PYBIND11_OVERRIDE_PURE(std::string, Animal1, go, n_times); }
    std::string name() override { PYBIND11_OVERRIDE(std::string, Animal1, name, ); }
};
class PyDog1 : public Dog1 {
public:
    using Dog1::Dog1; // Inherit constructors
    std::string go(int n_times) override { PYBIND11_OVERRIDE(std::string, Dog1, go, n_times); }
    std::string name() override { PYBIND11_OVERRIDE(std::string, Dog1, name, ); }
    std::string bark() override { PYBIND11_OVERRIDE(std::string, Dog1, bark, ); }
};


// 从带有虚拟方法的pybind11注册类派生的注册类需要类似的蹦床类，即使这个注册派生类本身没有明确声明或重写任何虚拟方法：
class Husky : public Dog1 {};
class PyHusky : public Husky {
public:
    using Husky::Husky; // Inherit constructors
    std::string go(int n_times) override { PYBIND11_OVERRIDE_PURE(std::string, Husky, go, n_times); }
    std::string name() override { PYBIND11_OVERRIDE(std::string, Husky, name, ); }
    std::string bark() override { PYBIND11_OVERRIDE(std::string, Husky, bark, ); }
};

// 然而，有一种技术可以用来避免这种重复（这对于具有多个虚拟方法的基类特别有用）。该技术涉及使用模板蹦床课程，如下所示：
// 这种方法，可以避免 pybind11注册类派生 的基类有纯虚方法，且本身没有定义额外的虚函数时，pybind11注册类派生 需要机器排上的问题。
template <class AnimalBase = Animal1> class PyAnimal2 : public AnimalBase {
public:
    using AnimalBase::AnimalBase; // Inherit constructors
    std::string go(int n_times) override { PYBIND11_OVERRIDE_PURE(std::string, AnimalBase, go, n_times); }
    std::string name() override { PYBIND11_OVERRIDE(std::string, AnimalBase, name, ); }
};


// template <class DogBase = Dog> class PyDog : public PyAnimal<DogBase> {
// public:
//     using PyAnimal<DogBase>::PyAnimal; // Inherit constructors
//     // Override PyAnimal's pure virtual go() with a non-pure one:
//     std::string go(int n_times) override { PYBIND11_OVERRIDE(std::string, DogBase, go, n_times); }
//     std::string bark() override { PYBIND11_OVERRIDE(std::string, DogBase, bark, ); }
// };