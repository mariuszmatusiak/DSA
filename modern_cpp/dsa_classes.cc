#include "dsa_classes.h"

void ExampleOne::printState() const {
    std::cout << "This is not inlined." << std::endl;
    std::cout << "a is " << a << " and b is " << b << ", and c is " << c << std::endl;
}

ExampleOne ExampleOne::operator+(const ExampleOne& right_hand_arg) const {
    // std::cout << "Overloaded sum operator is being called." << std::endl;
    ExampleOne result;
    result.a = a + right_hand_arg.a;
    result.b = b + right_hand_arg.b;
    // std::cout << "Temporary result object address: " << &result << std::endl;
    return result;
}

ExampleOne& ExampleOne::operator+=(const ExampleOne& right_hand_arg) {
    // std::cout << "Overloaded += operator is being called." << std::endl;
    this->a += right_hand_arg.a;
    this->b += right_hand_arg.b;
    // to return a reference to myself I need to use this pointer dereference
    return *this;
}

ExampleOne::~ExampleOne() { // Virtual keywords is necessary only in the declaration. DO NOT confuse with const keyword.
    std::cout << "Killing " << this << std::endl;
}
