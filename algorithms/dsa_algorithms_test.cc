#include "dsa_algorithms.h"

#include <gtest/gtest.h>    // Required GoogleTest import
#include <chrono>           // C++ style time measurement
#include <ctime>            // C style time measurement
#include <pthread.h>        // GoogleTest is pthread-safe  according to docs
#include <string>

// #include <print>         //since C++23
#include <limits>

using namespace DSA::Utils;

using std::string;

using DSA::Algorithms::swapElements;
using DSA::Algorithms::Sorting::bubbleSort;
using DSA::Algorithms::Sorting::SortingFunPtr;
using DSA::Algorithms::BitManipulation::getBit;

using DSA::Utils::log;

namespace DSA::Tests {

TEST(HelloTest, Basic) {
    EXPECT_STRNE("HELLO","WORLD");     // EXPECT_ doesn't terminate on failure
    EXPECT_EQ(5*10, 50);    // ASSERT_ does terminate immediately (MAY cause memory leaks due to that)
    EXPECT_NE(2+2*2, 8) << "Testing that 2+2*2 != 8\n";     // Additional messages go through <<
}

class TestSuiteFixture : public testing::Test { // or ::testing::Environment for global SetUps
protected:     // required by GoogleTest
    // any object I plan to reuse
    // always created a fresh one for a test
    std::time_t t0_CStyle {};
    std::chrono::time_point<std::chrono::steady_clock> t0_CppStyle {};

    virtual void SetUp() override {
        // prepare objects for testing
        // override to double sure I use the proper method
        t0_CStyle = std::time(nullptr);
        t0_CppStyle = std::chrono::steady_clock::now();
    }

    virtual void TearDown() override {
        // release objects after testing
        std::time_t endTime_CStyle {std::time(nullptr)};
        auto endTime_CppStyle {std::chrono::steady_clock::now()};

        double diffTime_CStyle {std::difftime(endTime_CStyle, t0_CStyle)};
        std::chrono::duration<double> diffTime_CppStyle { (endTime_CppStyle - t0_CppStyle) };
        log(std::format("Test execution time: {}s (C), {}s (C++).\n", diffTime_CStyle, diffTime_CppStyle));
    }

    // TestSuiteFixture() noexcept {}

    // virtual ~TestSuiteFixture() {}
};

class BubbleSortTestSuite : public TestSuiteFixture {

};

class SwapElementsTestSuite : public TestSuiteFixture {
protected:
    std::vector<int> pairvec = {2, -5};
};

TEST(SwapSuite, SortInts) {
    std::vector<int> pairvec = {2, -5};
    EXPECT_EQ(pairvec[0], 2);
    EXPECT_EQ(pairvec[1], -5);
    swapElements(&pairvec[0], &pairvec[1]);
    EXPECT_EQ(pairvec[0], -5);
    EXPECT_EQ(pairvec[1], 2);
}

// this is the same test as above but uses fixture class and _F()
TEST_F(SwapElementsTestSuite, SortInts) {
    // std::println("C++23 support");
    // printContainer(pairvec);
    EXPECT_EQ(pairvec[0], 2);
    EXPECT_EQ(pairvec[1], -5);
    swapElements(&pairvec[0], &pairvec[1]);
    // printContainer(pairvec);
    EXPECT_EQ(pairvec[0], -5);
    EXPECT_EQ(pairvec[1], 2);
}

TEST_F(BubbleSortTestSuite, BaseSort) {
    SortingFunPtr<std::vector<int>> = &bubbleSort<std::vector<int>>;
    constexpr int sorted[] = {
        std::numeric_limits<int>::min(),
        0, 1, 2, 4, 5,
        std::numeric_limits<int>::max()};
    std::vector<int> v {0, 2, 1, 5, 4, std::numeric_limits<int>::min(), std::numeric_limits<int>::max()};
    SortingFunPtr<std::vector<int>>(v, true);
    for (size_t i = 0u; i < sizeof(sorted)/sizeof(int); ++i) {
        EXPECT_EQ(sorted[i], v[i]);
    }
}

TEST_F(BubbleSortTestSuite, DescendingSort) {
    constexpr int sorted[] = {
        std::numeric_limits<int>::min(),
        0, 1, 2, 4, 5,
        std::numeric_limits<int>::max()};
    std::vector<int> v {0, 2, 1, 5, 4, std::numeric_limits<int>::min(), std::numeric_limits<int>::max()};
    bubbleSort(v, false);
    for (size_t i = 0u; i < sizeof(sorted)/sizeof(int); ++i) {
        EXPECT_EQ(sorted[v.size()-1u-i], v[i]);
    }
}

TEST_F(BubbleSortTestSuite, BestCaseSort) {
    constexpr int sorted[] = {
        std::numeric_limits<int>::min(),
        0, 1, 2, 4, 5,
        std::numeric_limits<int>::max()};
    std::vector<int> v (sorted, sorted + 7);
    bubbleSort(v);
    for (size_t i = 0u; i < sizeof(sorted)/sizeof(int); ++i) {
        EXPECT_EQ(sorted[i], v[i]);
    }
}

TEST_F(BubbleSortTestSuite, WorstCaseSort) {
    constexpr int sorted[] = {
        std::numeric_limits<int>::min(),
        0, 1, 2, 4, 5,
        std::numeric_limits<int>::max()};
    std::vector<int> v (sorted, sorted + 7);
    bubbleSort(v, false);
    for (size_t i = 0u; i < sizeof(sorted)/sizeof(int); ++i) {
        EXPECT_EQ(sorted[v.size()-1u-i], v[i]);
    }
}

TEST(BitManipulationSuite, RightShift) {
    int b = -16;
    EXPECT_EQ(b >> 1, -8);
    // Step 1. Invert bits in positive repr - 0b00010000 -> 0b11101111
    // Step 2. Add 1 0b11101111 -> 0b11110000
    // OR
    // Step 1. Take -1 * 2^N = -1 * 2^7 = -128
    // Step 2. Set the remaining value -128 + *112* = -16 => 112 = 64 + 32 + 16 => -1 * 2^7 + 1*2^6 + 1*2^5 + 1*2^4 -> 0b11110000
    int8_t binary_b = 0b11110000;
    const int8_t binary_b_check = 0b11111000;
    EXPECT_EQ(binary_b >>  1, binary_b_check);
    // EXPECT_EQ(binary_b >>> 1, 0b01111000); //not supported
}

TEST(BitManipulationSuite, getBit) {
    uint8_t a = 0b11011111;
    EXPECT_EQ(getBit(a, 5), false);
    EXPECT_EQ(getBit(a, 7), true);
    EXPECT_EQ(getBit(a, 9), false);
}

// C++ std::sort employs introsort, i.e. a combination of quicksort, heapsort and inserion sort
// Complexity O(NlogN) - worst/best/average case
TEST(StandardAlgorithms, Sort) {
    std::deque<string> words {"ala", "ma", "kota", "a", "kot", "ma", "ale"};
    printContainer(words);
    std::sort(words.begin(), words.end());
    printContainer(words);
    std::sort(words.rbegin(), words.rend());
    printContainer(words);
    std::sort(words.begin(), words.begin()+4);
    printContainer(words);
    EXPECT_EQ(words.front(), "kot");
    EXPECT_EQ(words.back(), "a");
    // Custom sort by word length
    std::sort(words.begin(), words.end(), [](const string& word1, const string& word2) {return word1.size() < word2.size(); }); // ascending by size
    printContainer(words);
}

TEST(StandardAlgorithms, Find) {
    std::deque<string> words {"ala", "ma", "kota", "a", "kot", "ma", "ale"};
    printContainer(words);
    // find kot
    auto it = std::find(words.begin(), words.end(), "kot");
    EXPECT_EQ("kot", *it);
    // std::cout << *it << std::endl;
}

TEST(StandardAlgorithms, FirstElementGreaterThan) {
    std::deque<string> words {"ala", "ma", "kota", "a", "kot", "ma", "ale"};
    printContainer(words);
    // find kot
    std::sort(words.begin(), words.end());
    auto it = std::upper_bound(words.begin(), words.end(), "k"); // >=k
    EXPECT_EQ("kot", *it);
    // std::cout << *it << std::endl;
}

TEST(StandardAlgorithms, MinElement) {
    std::deque<string> words {"ala", "ma", "kota", "a", "kot", "ma", "ale"};
    printContainer(words);
    // find a
    auto it = std::min_element(words.begin(), words.end());
    EXPECT_EQ("a", *it);
    // std::cout << *it << std::endl;
    it = std::max_element(words.begin(), words.end());
    EXPECT_EQ("ma", *it);
    // std::cout << *it << std::endl;
}

TEST(StandardAlgorithms, CopyAndFill) {
    std::deque<string> words {"ala", "ma", "kota", "a", "kot", "ma", "ale"};
    std::vector<string> copiedWords(words.size()); // init vector for 7 elements - required
    std::copy(words.begin(), words.end(), copiedWords.begin());
    printContainer(copiedWords);
    std::fill(words.begin(), words.end(), "ala");
    printContainer(words);
}

TEST(StandardAlgorithms, BinarySearch) {
    std::vector<int> v {3, 6, 1, 2, 9, 10, 12, 15, 3, 0};
    // sort first
    std::sort(v.begin(), v.end());
    printContainer(v);
    EXPECT_EQ(std::binary_search(v.begin(), v.end(), 12), true);
    EXPECT_EQ(std::binary_search(v.begin(), v.end(), 4), false);
}

TEST(StandardAlgorithms, MakeHeap) {
    std::vector<int> v {3, 6, 1, 2, 9, 10, 12, 15, 3, 0};
    std::make_heap(v.begin(), v.end());
    printContainer(v);
}

}
