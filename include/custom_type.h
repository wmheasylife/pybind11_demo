#pragma once

#include <string>


struct Pet{
public:
    Pet(const std::string &name) : name(name) {}
    void setName(const std::string &name_) { name = name_; }
    const std::string &getName() const { return name; }
    std::string name;

    void setFirstName(const std::string &fname) { first_name = fname; }
    const std::string &getFirstName() const { return first_name; }

private:

    std::string first_name;

};


struct Dog : Pet {
    Dog(const std::string &name) : Pet(name) { }
    std::string bark() const { return "woof!"; }
};




struct Pet2{
public:
    Pet2(const std::string &name) : name(name) {}
    void setName(const std::string &name_) { name = name_; }
    const std::string &getName() const { return name; }
    std::string name;
};

struct Dog2 : Pet2 {
    Dog2(const std::string &name) : Pet2(name) { }
    std::string bark() const { return "2woof!"; }
};


struct PolymorphicPet {
    virtual ~PolymorphicPet() = default;
};

struct PolymorphicDog : PolymorphicPet {
    std::string bark() const { return "woof!"; }
};



struct Pet3 {
    Pet3(const std::string &name, int age) : name(name), age(age) { }

    void set(int age_) { age = age_; }
    void set(const std::string &name_) { name = name_; }

    void set_v2(int age_) { age2 = age_; }
    void set_v2(const std::string &name_) { name2 = name_; }



    std::string name;
    int age;

    std::string name2;
    int age2;

};


struct Pet4 {
    enum Kind { // internal types and Enumerations
        Dog = 0,    
        Cat 
    };

    struct Attributes {
        float age = 0;
    };

    Pet4(const std::string &name, Kind type) : name(name), type(type) { }

    std::string name;
    Kind type;
    Attributes attr;
};




struct Widget {
    int foo(int x, float y) {return x*y;};
    int foo(int x, float y) const {return x*x + y*y;};
};


class Math {
public:
    static int add(int a, int b) {
        return a + b;
    }
};



