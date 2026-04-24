#ifndef DSA_ADAPTER_H
#define DSA_ADAPTER_H

#include <iostream>

namespace DSA::DesignPatterns {

class NewComponent {
public:
    virtual void doSthTheNewWay() const {
        std::cout << "Bonjour! from " << this << std::endl;
    }
    virtual ~NewComponent() {} // always add virtual dtor if inheritence is employed (warnings appear instead)
};

class OldComponent {
public:
    virtual void doSthTheOldWay() const {
        std::cout << "Hello! from " << this << std::endl;
    }
    virtual ~OldComponent() {} // always add virtual dtor if inheritence is employed (warnings appear instead)
};

class Adapter : public NewComponent {
private:
    const OldComponent& adapteeRef;
public:
    Adapter () = delete;                    ///< An empty constructor disabled
    Adapter (const OldComponent& adaptee);  ///< A default single-argument constructor
    Adapter (const Adapter& rhs);           ///< A copy constructor with an lvalue reference
    Adapter (Adapter&& rvr) noexcept;       ///< A move constructor with an rvalue reference, obligatory marked with noexcept

    ~Adapter() final;                       ///< An overriden final virtual destructor

    void doSthTheNewWay() const override
    {
        NewComponent::doSthTheNewWay();
        std::cout << "calling ";
        adapteeRef.doSthTheOldWay();
        std::cout << "from " << this << std::endl;
    }
};


} /* namespace DSA::DesignPatterns */

#endif /* DSA_ADAPTER_H */
