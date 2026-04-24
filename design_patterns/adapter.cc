#include "adapter.h"

#include <utility>  // std::move()

namespace DSA::DesignPatterns {

Adapter::Adapter (const OldComponent& adaptee) : adapteeRef{adaptee} {
    std::cout << this << " constructed with argument: " << &adaptee << std::endl;
}

Adapter::Adapter (const Adapter& rhs) : adapteeRef{rhs.adapteeRef} {
    std::cout << this << " constructed copying: " << &rhs << std::endl;
}

Adapter::Adapter (Adapter&& rvr) noexcept : adapteeRef{std::move(rvr.adapteeRef)} {
    std::cout << this << " constructed moving: " << &rvr << " and " << &rvr.adapteeRef << std::endl;
}

Adapter::~Adapter() {
    std::cout << this << " is killed." << std::endl;
}

}  /* namespace DSA::DesignPatterns */
