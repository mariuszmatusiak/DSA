#ifndef DSA_UTILS_H
#define DSA_UTILS_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <concepts> // for adding constraing to templates
#include <limits>   // for std::numeric_limits

using namespace std::literals::string_literals;

namespace DSA::Utils {

static constexpr bool verbose {false};

template<typename T>
inline T constexpr MAX() {return std::numeric_limits<T>::max(); }

template<typename T>
inline T constexpr MIN() {return std::numeric_limits<T>::min(); }

template<typename T>
inline T constexpr LOWEST() {return std::numeric_limits<T>::lowest(); }

bool isIn(const std::string_view& part, const std::string_view& longString);

char toLowerCase(char arg);

/**
 * Checks a given string for duplicate characters.
 * Returns the index of a first found duplicate character or 0 if no duplicates.
 */
int hasDuplicate(const std::string_view& str);

std::string getNextKLongSubstring(const std::string& str, const size_t K, const size_t pos = 0u);

std::unordered_set<std::string> generateKLongSubstrings(const std::string& str, const size_t K);

/* Template functions definitions are allowed to be placed in header files.
   Internally they are treated as inlines (according to learncpp.com) so ODR rule still applies. */

template<typename T>
inline auto formatPtr(const T& arg) { return static_cast<const void *>(&arg); }
// template<typename T>
// inline auto formatPtr(const T* const arg) { return static_cast<const void *>(arg); }

template<typename T>
concept NumericConstraint = std::integral<T> || std::floating_point<T>;

template<typename T>
concept CustomNumericConstraint = requires(T arg) {
    arg+1; // expression which must compile in order to constraint work
    arg*1; // expression which must compile in order to constraint work
};

template<typename T>
void log(const T c_str, bool force = false) {
    if (verbose || force) {std::cout << c_str << std::endl;}
}

template<typename T> // since C++20 this can also be replaced with autos
void printContainer(const T& container, bool force = false) {
    if (verbose || force) {
        std::cout << "[ ";
        for (auto& elem : container) {
            std::cout << elem << ", ";
        }
        std::cout << "]" << std :: endl;
    }
}

template<typename T>
void printMap(const T& container, bool force = false) {
    if (verbose || force) {
        std::cout << "[ " << std::endl;
        for (auto& kv : container) {
            std::cout << kv.first << " -> " << kv.second << std::endl;
        }
        std::cout << "]" << std :: endl;
    }
}

template<typename T> // since C++20 this can also be replaced with autos
void printHeap(const T& container, bool force = false) {
    T copiedContainer(container);
    if (verbose || force) {
        std::cout << "[ ";
        while(!copiedContainer.empty()) {
            std::cout << copiedContainer.top() << ", ";
            copiedContainer.pop();
        }
        std::cout << "]" << std :: endl;
    }
}

template<typename T>
void printContainerInfo(const T& container, bool force = false)
{
    if (verbose || force) {
        size_t index {0};
        std::cout << "Size of container: " << container.size() << " elements." << std::endl;
        std::cout << "Size of data: " << sizeof(container) << std::endl;
        for (auto& elem : container)
        {
            printf("[%lu] %d, address %p\n", index++, elem, formatPtr(elem));
            // std::cout << "[" << index++ << "] " << elem << std::endl;
        }
        // or
        // for (index = 0; index < container.size(); index++)
        // {
        //    printf("[%llu] %d, address %p\n", index, container[index], formatPtr(container[index]));
        // }
    }
}

template<typename... Args> // multiple-param template
void printAll(Args&&... args) {
    std::cout << std::format("Placeholder {} {} {}...", args...) << std::endl;
}

enum class NitroRules : char {
    A = 'A',
    C = 'C',
    G = 'G',
    T = 'T'
};

const std::unordered_map<NitroRules, NitroRules> NitroPairs {
    { NitroRules::A, NitroRules::T },
    { NitroRules::T, NitroRules::A },
    { NitroRules::G, NitroRules::C },
    { NitroRules::C, NitroRules::G }
};

}

namespace DSA::OtherUtils {

//print() is available since C++23:
constexpr void print(const std::string_view str_fmt, auto&&... args)
{
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

}

#endif // DSA_UTILS_H
