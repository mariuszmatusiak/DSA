#ifndef DSA_CLASSES
#define DSA_CLASSES

#include <format>
#include <iostream>
#include <compare>      // for <=> operator
#include <span>

enum RegularEnum
{
    A,
    B
};

enum TypeEnum : uint8_t
{
    C,
    D = 255
};

enum class ClassEnum : uint8_t // doesn't allow to be implicitly casted to uint
{
    E,
    F
};

struct UnitializedStruct {
    char a;
    short b;
    int c;
    long long int d;

    void print() const {
        std::cout << std::format("Structure content:\na='{}' b={} c={} d={}.\nTotal size: {}", a, b, c, d, sizeof(*this)) << std::endl;
    }
};

struct InitializedStruct {
    char a {};
    short b {};
    int c {};
    long long int d {};

    void print() const {
        std::cout << std::format("Structure content:\na='{}' b={} c={} d={}.\nTotal size: {}", a, b, c, d, sizeof(*this)) << std::endl;
    }
};

class ExampleOne {
    //private by default
    int privateMember {250};
protected:
    int protectedMember {500};
public:
    int publicMember {1000};
    uint64_t a; // this is initialized to mess if not assigned explicitly
    uint32_t b = 0u;
    const uint16_t c;

    ExampleOne();
    ExampleOne(uint16_t arg);
    ExampleOne(const ExampleOne&); // copy constructor, assign to =delete; to disable it and prevent compiler from providing one explicitly
    ExampleOne& operator= (const ExampleOne&); // copy/assignment operator, assign to =delete; to disable it and prevent compiler from providing one explicitly
    ExampleOne operator+(const ExampleOne& right_hand_arg) const; //TODO check how to override operator<<
    ExampleOne& operator+=(const ExampleOne& right_hand_arg);
    bool operator==(const ExampleOne& otherObj) const {
        return ((a == otherObj.a) && (b == otherObj.b) && (c == otherObj.c));
    }
    virtual ~ExampleOne();

    void printState() const; // allows to be called if const reference is used
    void printWOConst() { std::cout << "This won't be called using const reference" << std::endl; }
    virtual void printHi() const { std::cout << "This is inlined automatically" << std::endl; }
    void throwException() { throw std::runtime_error("An example runtime error to handle."); }
};

class ExampleTwo : public ExampleOne {
protected:
    int privateMember {300};
public:
    void printHi() const override {
        ExampleOne::printHi(); // called from the super class, doesn't need 'this'
        std::cout << "This is also inlined\n" << std::format("Private guts {}\nProtected guts {}\nPublic guts {}", privateMember, protectedMember, publicMember) << std::endl; // privateMember here is not inherited from the base class
    } // The override here is redundant. Only for clarification that we override a method.
    virtual void printBye() const /* override */  {std::cout << "Bye!" << std::endl;} // e.g. this doesn't compile with override
};

class ExampleThree : public ExampleOne {
public:
    void printHi() const override {
        std::cout << "This is call from ExampleThree class." << std::endl;
    }
};

struct ExamplesHi {
    // A functor for all the types
    void operator()(const ExampleTwo& o) const { o.printHi(); }
    void operator()(const ExampleThree& o) const { o.printHi(); }
};

template<typename T>
class Fraction { // A custom Fraction class
    T num;
    T den;
public:
    Fraction() = delete;
    constexpr Fraction(const T num_) : num(num_), den(1) {}
    constexpr Fraction(const T num_, const T den_) : num(num_), den(den_) {}
    T getNumerator()   const { return num; }
    T getDenominator() const { return den; }

    constexpr double toDouble() const {
        return static_cast<double>(num) / static_cast<double>(den);
    }

    //auto operator <=> (const Fraction& rhs) const = default; // definition of the basic spaceship operator, works fine for a single var wrapper, but not for fractions
    constexpr auto operator <=> (const Fraction& rhs) const { // these two overloads are needed for more complex objects:
        return toDouble() <=> rhs.toDouble();
    }
    constexpr auto operator == (const Fraction& rhs) const {
        return toDouble() == rhs.toDouble();
    }
    constexpr auto operator != (const Fraction& rhs) const { // for some reason this is additionally required on macOS
        return toDouble() != rhs.toDouble();
    }
};

template<typename T> // A custom Fraction formatter
struct std::formatter<Fraction<T>> : std::formatter<int> {
    template<typename Context>
    auto format(const Fraction<T>& obj, Context& c) const {
        return format_to(c.out(), "({}) over ({})", obj.getNumerator(), obj.getDenominator());
    }
};

template<typename T>
auto toSpanView(const std::span<T> array) {
    return array;
}

#endif // DSA_CLASSES
