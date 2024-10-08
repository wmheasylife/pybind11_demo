#pragma once

#include <memory>
#include <string>
#include <iostream>

class Example {
public:
    Example(int age, std::string& name) {
        this->age = age;
        this->name = name;
    } // private constructor

    int get_age() {
        return age;
    }

    const std::string& get_name() {
        return name;
    }


private:
    int age;
    std::string name;

};

std::unique_ptr<Example> create_example(int age, std::string& name) {
    return std::unique_ptr<Example>(new Example(age, name)); 
}


void show_example(std::unique_ptr<Example> ex) {
    std::cout << "Example ins, age:" << ex->get_age() << ", name:" << ex->get_name() << std::endl;
}



class Pet {
public:
    Pet(const std::string &name) : name(name) {}
    void setName(const std::string &new_name) { name = new_name; }
    std::string getName() const { return name; }
    ~Pet() {
        std::cout << "Pet instance name:" << name << " destory ! " << std::endl;
    }

private:
    std::string name;

};

