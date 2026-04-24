#include "dsa_algorithms.h"

namespace DSA::Algorithms::Math {

std::optional<unsigned long long> sfactorial (int n)
{
    constexpr unsigned long long result { 1ull };
    if (n < 0) {
        return {}; // default empty std::optional
    } else if ((n == 0u) || (n == 1u)) {
        return result;
    }
    else {
        auto recursiveResult = sfactorial(n-1); // contains also boolean .has_value()
        if (recursiveResult) { // or if (recursiveResult.has_value()) {...}
            return static_cast<unsigned long long>(n) * recursiveResult.value(); // or by dereference *recursiveResult
        } else {
            return {}; // default empty std::optional
        }
    }
}

unsigned long long factorial (unsigned int n)
{
    unsigned long long result = 1ull;
    if ((n == 0u) || (n == 1u))
        return result;
    else
        return static_cast<unsigned long long>(n) * factorial(n-1);
}

unsigned long long cfactorial (unsigned int n)
{
    return ((n == 0u) || (n == 1u)) ? 1u : static_cast<unsigned long long>(n) * cfactorial(n-1);
}

unsigned long long permutations (const unsigned int n, const unsigned int k)
{
    unsigned long long result = 1ull;
    if (k > n)
        throw std::runtime_error("k cannot be greater than n.");
    for (unsigned int i = n - k + 1; i <= n; ++i)
        result *= static_cast<unsigned long long>(i);
    return result;
}

// O(sqrt(n)) complexity
bool isPrimeNumber (unsigned long long n) {
    for (unsigned long long it = 2ull; it * it <= n; ++it) {
        if (n % it == 0)
            return false;
    }
    return true;
}

std::vector<unsigned long long> getPrimeNumbers (const unsigned long long max, const unsigned long long start) {
    std::vector<unsigned long long> primeArray {};
    primeArray.reserve(max); // reserve max of n
    // naive way, will be reduced using the aristo siete method
    for (unsigned long long i = start; i <= max; ++i)
    {
        if (isPrimeNumber(i)) {
            primeArray.push_back(i);
        }
    }
    primeArray.shrink_to_fit();
    return primeArray;
}

PermsAndCombs perms(const std::string& str)
{
    PermsAndCombs result {};
    result.noOfSubsets = 0;
    return result;
}

} // DSA::Algorithms::Math

/**********************************************/

namespace DSA::Algorithms::BitManipulation
{

bool getBit (int number, size_t pos) {
    return (number >> pos) & 1;
}
int setBit (int number, size_t pos) {
    return 0;
}
int clearBit (int number, size_t pos) {
    return 0;
}
int clearBitFromMSBToPos (int number, size_t pos) {
    return 0;
}
int clearBitFromZeroToPos (int number, size_t pos) {
    return 0;
}
int toggleBit (int number, size_t pos) {
    return 0;
}
int updateBit (int number, size_t pos, bool bitSet) {
    return 0;
}

} // DSA::Algorithms::BitManipulation

/**********************************************/
