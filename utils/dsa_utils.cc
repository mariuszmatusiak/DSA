#include "dsa_utils.h"

#include <iostream>

namespace DSA::Utils {

void printObject(const std::any& argument) {
    if (!argument.has_value()) {
        std::cout << "An empty argument given" << std::endl;
    } else {
        if (argument.type() == typeid(int)) {
            auto x = std::any_cast<int>(argument);
            std::cout << "The int is " << x << std::endl;
        } else if(argument.type() == typeid(std::string)) {
            auto x = std::any_cast<const std::string&>(argument);
            std::cout << "The string is " << x << std::endl;
        } else if(argument.type() == typeid(std::vector<int>)) {
            auto v = std::any_cast<const std::vector<int>&>(argument);
            std::cout << "The vector is " << std::endl;
            printContainer<std::vector<int>>(v, true);
        //} else if(argument.type() == typeid(std::unordered_map<T>)) {
        //    auto m = std::any_cast<const std::unordered_map<T>&>(argument);
        //    std::cout << "The map is " << std::endl;
        //    printMap(m, true);
        } else {
            std::cout << std::format("The type {} not yet supported.", argument.type().name()) << std::endl;
        }
    }
}

bool isIn(const std::string_view& part, const std::string_view& longString) {
    //https://en.cppreference.com/w/cpp/string/basic_string.html
    return (longString.find(part) != std::string::npos);
}

// [a, z] == [97, 122]
// [A, Z] == [65, 90]
// [0, 9] == [48, 57]
char toLowerCase(char arg) {
    constexpr size_t offset {'a' - 'A'};
    char result {arg};
    if (arg >= 'A' && arg <= 'Z') {
        result += offset;
    }
    return result;
}

int hasDuplicate(const std::string_view& str) {
    int result {0};
    if (str.size() >= 2) {
        std::unordered_set<char> charHashSet {*str.begin()};
        for (size_t idx = 1u; idx < str.size(); ++idx) {
            if (charHashSet.contains(str[idx])) {
                result = idx;
                break;
            } else {
                charHashSet.insert(str[idx]);
            }
        }
    }
    return result;
}

std::string getNextKLongSubstring(const std::string& str, const size_t K, const size_t pos) {
    const size_t count { ( pos <= (str.size() - K) ) ? K : ( str.size() - pos ) };
    return str.substr(pos, count);
}

std::unordered_set<std::string> generateKLongSubstrings(const std::string& str, const size_t K) {
    // K - sliding window size
    std::unordered_set<std::string> substrings {};
    if (K > 0) {
        if (K < str.size()) {
            for (size_t idx = 0u; (idx + K) <= str.size(); ++idx) {
                substrings.emplace(getNextKLongSubstring(str, K, idx));
            }
        } else {
            substrings.insert(str);
        }
    }
    return substrings;
}

int nonSubstringGenerationApproach(std::string s) {
    using HashMap = std::unordered_map<char, size_t>;
    if (s.size() < 2) { return s.size(); }
    int longestSubstring {0};
    int substringLength;
    size_t leftIdx  {0};
    size_t rightIdx {leftIdx + 1};
    HashMap substringChars {{s[leftIdx], leftIdx}};
    while (rightIdx < s.size()) {
        // For consequent duplicates:
        // if (s[rightIdx] == s[rightIdx-1])
        // For all duplicates:
        if (auto duplicate = substringChars.find(s[rightIdx]); duplicate != substringChars.end())
        {
            // reset sliding window, update leftIdx
            substringLength = rightIdx-1 - leftIdx + 1;
            if (substringLength > longestSubstring) {
                longestSubstring = substringLength;
            }
            leftIdx = duplicate->second + 1;
            //substringChars.clear();
        }
        substringChars.insert({s[rightIdx], rightIdx});
        ++rightIdx;
    }
    substringLength = rightIdx-1 - leftIdx + 1;
    if (substringLength > longestSubstring) {
        longestSubstring = substringLength;
    }
    return longestSubstring;
}

}
