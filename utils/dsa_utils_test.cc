#include "dsa_utils.h"

#include <gtest/gtest.h>
#include <climits>

using DSA::Utils::MAX;
using DSA::Utils::MIN;
using DSA::Utils::LOWEST;
using DSA::Utils::log;
using DSA::Utils::hasDuplicate;

namespace DSA::Utils::Tests {

class UtilsTestSuiteFixture : public testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(UtilsTestSuiteFixture, HasDuplicatePositive) {
    std::string a {"aabcdef"};
    EXPECT_EQ(hasDuplicate(a), 1);
}

TEST_F(UtilsTestSuiteFixture, HasDuplicatePositive2) {
    std::string a {"abcdefgf"};
    EXPECT_EQ(hasDuplicate(a), 7);
}

TEST_F(UtilsTestSuiteFixture, HasDuplicatePositive3) {
    std::string a {"aa"};
    EXPECT_EQ(hasDuplicate(a), 1);
}

TEST_F(UtilsTestSuiteFixture, HasDuplicateNegative) {
    std::string a {"abcdef"};
    EXPECT_EQ(hasDuplicate(a), 0);
}

TEST_F(UtilsTestSuiteFixture, HasDuplicateNegative2) {
    std::string a {"a"};
    EXPECT_EQ(hasDuplicate(a), 0);
}

TEST_F(UtilsTestSuiteFixture, GetSubstrings) {
    constexpr std::string a {"abcdef"};
    constexpr std::string b {"a"};
    constexpr size_t slidingWindowSize {a.size()};
    for (size_t slidingWindowSize = a.size(); slidingWindowSize > 0; --slidingWindowSize) {
        auto substrings = generateKLongSubstrings(a, slidingWindowSize);
        printContainer(substrings, true);
        EXPECT_EQ(substrings.size(), a.size() - slidingWindowSize + 1);
    }
    auto substrings = generateKLongSubstrings(b, 0);
    printContainer(substrings, true);
    EXPECT_EQ(substrings.size(), 0);
    substrings = generateKLongSubstrings(b, b.size());
    printContainer(substrings, true);
    EXPECT_EQ(substrings.size(), 1);
    substrings = generateKLongSubstrings(b, b.size()+1);
    printContainer(substrings, true);
    EXPECT_EQ(substrings.size(), 1);
}

TEST_F(UtilsTestSuiteFixture, Max) {
    constexpr int maxInt {MAX<int>()};
    constexpr size_t maxSize {MAX<size_t>()};
    constexpr unsigned long long maxUll {MAX<unsigned long long>()};
    constexpr float maxFlt {MAX<float>()};
    constexpr double maxDbl {MAX<double>()};
    constexpr long double maxlDbl {MAX<long double>()};
    EXPECT_EQ(maxInt,  INT_MAX);    // 2147483647
    EXPECT_EQ(maxSize, ULONG_MAX);  // 18446744073709551615
    EXPECT_EQ(maxUll,  ULLONG_MAX); // 18446744073709551615
    EXPECT_EQ(maxFlt,  FLT_MAX);    // 3.40282e+38
    EXPECT_EQ(maxDbl,  DBL_MAX);    // 1.79769e+308
    EXPECT_EQ(maxlDbl, LDBL_MAX);   // 1.79769e+308
    log(std::format("{}, size {}.", maxInt, sizeof(maxInt)));
    log(std::format("{}, size {}.", maxSize, sizeof(maxSize)));
    log(std::format("{}, size {}.", maxUll, sizeof(maxUll)));
    log(std::format("{}, size {}.", maxFlt, sizeof(maxFlt)));
    log(std::format("{}, size {}.", maxDbl, sizeof(maxDbl)));
    log(std::format("{}, size {}.", maxlDbl, sizeof(maxlDbl)));
}

TEST_F(UtilsTestSuiteFixture, Min) {
    constexpr int minInt {MIN<int>()};
    constexpr size_t minSize {MIN<size_t>()};
    constexpr unsigned long long minUll {MIN<unsigned long long>()};
    constexpr float minFlt {MIN<float>()};
    constexpr double minDbl {MIN<double>()};
    constexpr long double minlDbl {MIN<long double>()};
    EXPECT_EQ(minInt,  INT_MIN);    // -2147483648
    EXPECT_EQ(minSize, 0);          // 0
    EXPECT_EQ(minUll,  0);          // 0
    EXPECT_EQ(minFlt,  FLT_MIN);    // 1.1754944e-38
    EXPECT_EQ(minDbl,  DBL_MIN);    // 2.2250738585072014e-308
    EXPECT_EQ(minlDbl, LDBL_MIN);   // 2.2250738585072014e-308
    log(std::format("{}, size {}.", minInt, sizeof(minInt)));
    log(std::format("{}, size {}.", minSize, sizeof(minSize)));
    log(std::format("{}, size {}.", minUll, sizeof(minUll)));
    log(std::format("{}, size {}.", minFlt, sizeof(minFlt)));
    log(std::format("{}, size {}.", minDbl, sizeof(minDbl)));
    log(std::format("{}, size {}.", minlDbl, sizeof(minlDbl)));
}

TEST_F(UtilsTestSuiteFixture, Lowest) {
    constexpr int lowestInt {LOWEST<int>()};
    constexpr size_t lowestSize {LOWEST<size_t>()};
    constexpr unsigned long long lowestUll {LOWEST<unsigned long long>()};
    constexpr float lowestFlt {LOWEST<float>()};
    constexpr double lowestDbl {LOWEST<double>()};
    constexpr long double lowestlDbl {LOWEST<long double>()};
    EXPECT_EQ(lowestInt,  INT_MIN);     // -2147483648
    EXPECT_EQ(lowestSize, 0);           // 0
    EXPECT_EQ(lowestUll,  0);           // 0
    EXPECT_EQ(lowestFlt,  -FLT_MAX);    // -3.4028235e+38
    EXPECT_EQ(lowestDbl,  -DBL_MAX);    // -1.7976931348623157e+308
    EXPECT_EQ(lowestlDbl, -LDBL_MAX);   // -1.7976931348623157e+308
    log(std::format("{}, size {}.", lowestInt, sizeof(lowestInt)));
    log(std::format("{}, size {}.", lowestSize, sizeof(lowestSize)));
    log(std::format("{}, size {}.", lowestUll, sizeof(lowestUll)));
    log(std::format("{}, size {}.", lowestFlt, sizeof(lowestFlt)));
    log(std::format("{}, size {}.", lowestDbl, sizeof(lowestDbl)));
    log(std::format("{}, size {}.", lowestlDbl, sizeof(lowestlDbl)));
}

}
