# Modern C++ topics

## Summary
- The compiler settings:
  - ```g++ dsa_01.cpp -Wall -pedantic -o dsa.o -std=c++20 && ./dsa.o```
  - all warnings -Wall
  - `pedantic`
  - standard: `-std=c++20`

- CMake settings:
  1. Create main CMakeLists.txt with minimum version, project name and executable
  2. Create output folder, `cd` inside
  3. Configure project with `cmake ../`
  4. Build project with `cmake --build .`

- Indicating variables as unused:
  - `[[maybe_unused]]` (C++17 standard compliant)
  - `__attribute((unused))__` (GCC only)
  - `(void)var` - casting to void function parameterss

- `operator` overloading
- `override` keyword
- `virtual` in declarations
- `template<typename/class T>`
- basic& reference and temporary_object&& reference
- `try_{throw}_catch()` with `std::exception`
- Smart pointers
  - `std::shared_ptr<T>`
  - `std::unique_ptr<T>`
  - `std::weak_ptr<T>`
- Sequential data structures: lists, vectors, queues, dequeues
- Associated data structures: sets, maps
- Modern initialization techniques:
  - {} - list-initialized with empty list, best since C++11, for primitive types, for vectors it initializes with the given elements
  - () - a matching constructor
  - = - a regular copy-assignment operator since C
- `Lambda` -> anonymous function
  ```C++
  ()=> is
  [/* outside variables passed to scope */](/* fuction arguments */) {
      /* body of the function (with return) */
  }
  [x] - variable by value
  [&x] - variable by reference
  [=] - all variables in scope by value
  [&] - all variables in scope by reference
  ```
- logical and bitwise operators:
  - and == &&
  - or == ||
  - not == !
  - compl == ~
  - bitor == |
  - bitand == &
  - xor == ^
- constexpr
- alias:
  using mytype = uint16_t is the same as
  typedef mytype uint16_t;
- member and non-member operator overload
- `explicit` keyword in constructor - ensures there are no implicit conversions normally done by the *implicit type conversion*, e.g. casting double to int.gf
- default parameters - put in declarations
- Constructor() = delate; - removes default constructor (derived)
- noexcept() - compile-time check returning true if expression won't throw exceptions
- f() noexcept - function won't throw exception
- cout << formatters:
  - (ints) std::hex, std::showbase, std::oct, std::dec, std::noshowbase
  - (floats) std::fixed, std::scientific, std::setprecision
  - (strings) std::setw(itdth)(N), std::right (alignment), std::setfill('#') (padding)
  - operator string() <- string conversion operator for classes
- https://belaycpp.com/2022/02/15/constant-references-are-not-always-your-friends/
- copy assignment operator
- move assignment operator
- copy constructor
- move constructor
- using find() with lambda
- lambda syntax
  [ capture list ] (parameters) {mutable | constexpr | noexcept} -> return type {
    body of the function
  }, e.g.
- lambda type signature:
  - using jumpfunc = void(*)(); C-Style ptr to function
  - using jumpfunc = std::function<void()> - using function object
  - concept constraints for template
    #include <concepts>
    template<typename T>
    requires std::integral<T> || std::floating_point<T>
    concept Numeric = requires(T a) { //user-defined
     a+1; a*1;
    };
- string operations:
  - .front(), .back()
  - .data(), .c_str()
  - .size(), .length(), .empty()
  - .clear(), .insert(), .erase(), push_back, .pop_back(), .append(), +=, .replace(), .copy(), .swap()
  - .find(), .rfind(), .find_{first|last}_{not}_of()
  - .compare(), starts_with(), .ends_with()
  - .substr()
  - .sto(i|l|ll|ul|ull|f|d|ld)
- <random> header, Random Number Generators

- std::optional<T> class - for returning optional results
- std::any<T> class - for type-safe polymorphism and handling many classes
- std::variant<T> class [C++17] - type-safe union with std::visit() method
- structured bindings [C++17]
- Chrono library for time and interval measurements
  - Clocks:
  - system_clock - best to obtain current system time
  - steady_clock - best to calculate intervals/time diffs
- std::filesystem library
  - ::path
  - ::exists
  - ::is_directory
  - ::directory_entry
  - ::absolute
  - ::canonical
  - ::directory_iterator
  - ::relative
- std::format [C++20]
- spaceship operator - to replace all logical comparison operators with one, using the so-called "rewritten expressions" (C++20)
- integer comparison functions [C++20] (for signed/unsigned comparisons)
  - std::cmp_{less|less_equal|greater|greater_equal|equal|not_equal}
- std::span class - a container view-wrapper for C-arrays, vectors or STL array doesn't own
