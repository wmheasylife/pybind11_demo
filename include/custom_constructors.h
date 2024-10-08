#pragma once


class Example {
private:
    Example(int); // private constructor
public:
    // Factory function - returned by value:
    static Example create(int a) { return Example(a); }

    // // These constructors are publicly callable:
    // Example(double);
    // Example(int, int);
    // Example(std::string);
};


struct Aggregate {
    int a;
    std::string b;
};