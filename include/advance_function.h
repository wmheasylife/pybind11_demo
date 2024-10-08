#pragma once

int *get_data() { return new int(10); /* (pointer to a static data structure) */ }


class Holder {
public:
    Holder(int value) : value_(value) {}
    int getValue() const { return value_; }
private:
    int value_;
};

class Container {
public:
    Container() : holder_(new Holder(42)) {}
    Holder* getHolder() const { return holder_; }
private:
    Holder* holder_;
};


