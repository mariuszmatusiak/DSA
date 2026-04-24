#ifndef DSA_ALGORITHMS_H
#define DSA_ALGORITHMS_H

#include "dsa_utils.h"

#include <iostream>
#include <vector>
#include <array>
#include <utility>  // for std::move
#include <concepts> // for adding constraing and limitations to templates, since C++20
#include <algorithm>
#include <optional> // for std::optional<T> class

using namespace DSA::Utils;
using DSA::Utils::log;

/**********************************************/
namespace DSA::Algorithms {

/** Swap the T elements in place */
template<typename T>
void swapElements(T* const left, T* const right, bool useMoveSemantics = false)
{
    if (!useMoveSemantics) {
        const T temp = *left;
        *left = *right;
        *right = temp;
    } else {    // the same as std::swap
        T temp(std::move(*left));
        *left = std::move(*right);
        *right = std::move(temp);
    }
}

/**********************************************/
namespace Sorting {

template<typename T>
void (*SortingFunPtr) (T& container, bool ascending);

template<typename T>
void radixSort(T& container, bool ascending = true) {
}

template<typename T>
void quickSort(T& container, bool ascending = true) {
}

template<typename T>
void mergeSort(T& container, bool ascending = true) {
    // TODO assert that container is index-based accesible
    T helperArray {};
    helperArray.reserve(container.size()); // O(n) memory
}

template<typename T>// or template<NumericConstraint T> and without the next line or NumericConstraint can be used as a function argument type
void bubbleSort(T& container, bool ascending = true) {
    const size_t N = container.size();
    std::vector<size_t> swapsArray {};
    size_t iterations = 0u;
    size_t swaps;
    if (N < 2u) {
        return;  // Skip if there's one or no elements
    }
    do {
        ++iterations;
        swaps = 0u;
        for (size_t idx = 0u; idx < (N - 1u); ++idx)
        {
            if  ((ascending && (container[idx] > container[idx+1u])) ||
                (!ascending && (container[idx] < container[idx+1u])))
            {
                swapElements(&container[idx], &container[idx+1u]);
                ++swaps;
            }
        }
        swapsArray.push_back(swaps);
    } while (swaps); // optimize from O(N^2)
    log(std::format("Container sorted after {} iterations.\n", iterations));
}

} // Sorting

/**********************************************/
namespace Searching {

template <typename T>
int binarySearch(const T& sortedArray, const T element, const bool useStandard = false) {
    if (!useStandard) {
        // assume the given array is already sorted


    } else {

    }
}

template <typename T>
int ternarySearch(const T& sortedArray, const T element, const bool useStandard = false) {
    if (!useStandard) {


    } else {

    }
}

} // Searching

/**********************************************/
namespace Patterns {

/**
 * Examples:
 * - https://leetcode.com/problems/range-sum-query-immutable/description/
 * - https://leetcode.com/problems/contiguous-array/description/
 * - https://leetcode.com/problems/subarray-sum-equals-k/description/
 * Useful: cumulative sums, multiple sum queries
 */
template<NumericConstraint T>
std::vector<T> prefixSum(const std::vector<T>& array) {
    std::vector<T> sumVector {};
    T sum {};
    sumVector.reserve(array.size());
    for (size_t i = 0; i < array.size(); ++i) {
        sum += array[i];
        sumVector.push_back(sum); // operator[i] doesn't work here, must be pushed back
    }
    return sumVector;
}

template<typename T, T S>
requires NumericConstraint<T> // a regular bool expression, works with true, false, ||, etc
int conditionSum(T arg1, T arg2) {
    int result {};
    T sum = S;
    if ((arg1 + arg2) > sum) { result = -1; }
    else if ((arg1 + arg2) < sum) { result = 1; }
    else { result = 0; }
    return result;
}

/**
 * Examples:
 * - https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/
 * - https://leetcode.com/problems/3sum/description/
 * - https://leetcode.com/problems/container-with-most-water/description/
 * Useful: finding elements matching condition
 */
template<typename T>
auto twoPointers(const T* array, const size_t size, std::function<int(T, T)> conditionFun) {
    const T* first = &array[0];
    const T* last  = &array[size - 1];
    std::pair<T,T> leftAndRight {};
    while (first != last)
    {
        int compareResult = conditionFun(*first, *last);
        if (compareResult < 0) {
            --last;
        } else if (compareResult > 0) {
            ++first;
        } else {
            leftAndRight = std::make_pair(*first, *last);
            break;
        }
    }
    return leftAndRight;
}

template<typename T>
struct SlidingWindowResult {
    size_t leftIndex;
    size_t rightIndex;
    T value;
};

enum class SlidingWindowOp {
    SUM,
    AVG,
    MAX,
    MIN
};

template<typename T>
SlidingWindowResult<T> slidingWindow(const T* array, const size_t size, const size_t k, SlidingWindowOp op) {
    SlidingWindowResult<T> result {};
    if (k > size) {
        return result; // error
    }
    T resultValue {};
    switch(op)
    {
        case SlidingWindowOp::MAX:
            for (int i=0; i<k; ++i) {
                resultValue += array[i];
            }
            break;
        default: // to be added
            break;
    }
    // store initial value
    result.value = resultValue;
    result.leftIndex = 0;
    result.rightIndex = k-1;
    // let's slide
    for (int i = k; i <= (size - k); ++i)
    {
        switch (op)
        {
        case SlidingWindowOp::MAX:
            resultValue = resultValue + array[i] - array[i-k];
            if (resultValue > result.value)
            {
                result.value = resultValue;
                result.leftIndex = i - k + 1;
                result.rightIndex = i;
            }
            break;
        default:
            break;
        }
    }
    return result;
}

} // Patterns

/**********************************************/
namespace Math {

// New way with optional
std::optional<unsigned long long> sfactorial (int n);
// Old way:
unsigned long long factorial (unsigned int n); //p. 51
unsigned long long cfactorial (unsigned int n);

unsigned long long permutationsWithDuplicates (const unsigned int n, const unsigned int k);
unsigned long long permutationsWODuplicates (const unsigned int n, const unsigned int k);

bool isPrimeNumber (unsigned long long n); // p. 50
std::vector<unsigned long long> getPrimeNumbers (const unsigned long long max, const unsigned long long start = 2);
std::vector<int> getPrimeNumbersSiete (unsigned long long max, unsigned long long start = 2);

unsigned long long fibonacciNthElement (unsigned long long); //p.53
std::vector<unsigned long long> fibonacciSeries(unsigned long long); //memoization technique
// extra problems p.56

struct PermsAndCombs {
    std::vector<std::string> permutations {};
    std::vector<std::string> kth_permutations {};
    std::vector<std::string> unique_combinations {};
    std::vector<std::string> subsets {};
    size_t noOfSubsets {};
};
PermsAndCombs perms(const std::string& str);
PermsAndCombs perms(const char * str);

} // Math

/**********************************************/
namespace BitManipulation {

bool  getBit (int number, size_t pos);
int   setBit (int number, size_t pos);
int clearBit (int number, size_t pos);
int clearBitFromMSBToPos (int number, size_t pos);
int clearBitFromZeroToPos (int number, size_t pos);
int toggleBit (int number, size_t pos);
int updateBit (int number, size_t pos, bool bitSet = true);

} // BitManipulation

}

#endif // DSA_ALGORITHMS_H
