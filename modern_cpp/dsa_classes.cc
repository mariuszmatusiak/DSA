#include "dsa_classes.h"

void ExampleOne::printState() const {
    std::cout << "This is not inlined." << std::endl;
    std::cout << "a is " << a << " and b is " << b << ", and c is " << c << std::endl;
}

ExampleOne::ExampleOne() : c(0u) {
    std::cout << "Creating " << this << std::endl;
}

ExampleOne::ExampleOne(uint16_t arg) : c(arg) {
    std::cout << "Creating " << this << " with " << arg << std::endl;
}

ExampleOne::ExampleOne(const ExampleOne& o) : c(o.c) {
    std::cout << "A copy ctor for " << this << " copying " << &o << std::endl;
    this->privateMember = o.privateMember;
    this->protectedMember = o.protectedMember;
    this->publicMember = o.publicMember;
    this->a = o.a;
    this->b = o.b;
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
