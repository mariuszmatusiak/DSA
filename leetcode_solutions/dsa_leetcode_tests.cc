#include "dsa_leetcode.h"
#include "dsa_utils.h"
#include "dsa_algorithms.h"

#include <gtest/gtest.h>    // Required GoogleTest import

using namespace DSA::LeetCode;

using DSA::Algorithms::Patterns::prefixSum;
using DSA::Algorithms::Patterns::twoPointers;
using DSA::Algorithms::Patterns::conditionSum;
using DSA::Algorithms::Patterns::slidingWindow;
using DSA::Algorithms::Patterns::SlidingWindowOp;

namespace DSA::LeetCode::Tests {

class SolutionTest : public testing::Test {
protected:
    Solution solution {};
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(SolutionTest, removeDuplicates) {
    std::vector<int> v {0, 0, 1, 2, 3, 3, 3, 50, 50, 89, 90, 100, 100, 1001 };
    int k = solution.removeDuplicates(v);
    EXPECT_EQ(k, 9);
}

TEST_F(SolutionTest, findSubarrayToSort) {
    // auto binding
    std::vector<int> v {0, 1, 2, 5, 4, 6, 3, 8, 9, 10};
    auto [leftIndx, rightIndx] = solution.findSubarrayToSort(v.data(), v.size()); // structure binding
    EXPECT_EQ(leftIndx, 3);
    EXPECT_EQ(rightIndx, 6);
}

TEST_F(SolutionTest, findMajorityElement1) {
    std::vector<int> v {3, 2, 3};
    EXPECT_EQ(solution.majorityElement(v), 3);
}

TEST_F(SolutionTest, findMajorityElement2) {
    std::vector<int> v {2, 2, 1, 1, 1, 2, 2};
    EXPECT_EQ(solution.majorityElement(v), 2);
}

TEST_F(SolutionTest, findMajorityElement3) {
    std::vector<int> v {0, 1, 2, 3, 3, 3, 3};
    EXPECT_EQ(solution.majorityElement(v), 3);
}

TEST_F(SolutionTest, findMajorityElement4) {
    std::vector<int> v {1, 2};
    EXPECT_EQ(solution.majorityElement(v), 1);
}

TEST_F(SolutionTest, findMajorityElement5) {
    std::vector<int> v {999};
    EXPECT_EQ(solution.majorityElement(v), 999);
}

TEST(UtilsTest, prefixSum_Empty) {
    std::vector<int> v {};
    auto vSum = prefixSum(v);
    ASSERT_EQ(vSum.size(), v.size());
}

TEST(UtilsTest, prefixSum_NonEmpty) {
    std::vector<int> v {1, 2, 3, 4, 5};
    auto vSum = prefixSum(v);
    ASSERT_EQ(vSum.size(), v.size());
    EXPECT_EQ(vSum[0], 1);
    EXPECT_EQ(vSum[1], 3);
    EXPECT_EQ(vSum[2], 6);
    EXPECT_EQ(vSum[3], 10);
    EXPECT_EQ(vSum[4], 15);
}

TEST(UtilsTest, prefixSum_ComputeSum) {
    std::vector<int> v {1, 2, 3, 4, 5};
    auto vSum = prefixSum(v);
    ASSERT_EQ(vSum.size(), v.size());
    // Find sum from i to j
    constexpr size_t i = 2;
    constexpr size_t j = 3;
    EXPECT_EQ((3+4),(vSum[j]-vSum[i-1]));
}

TEST(UtilsTest, twoPointers_ComputeSum) {
    int v[] = {1, 2, 3, 4, 8};
    auto pair = twoPointers<int>(v, (sizeof(v)/sizeof(int)), conditionSum<int, 7>);
    EXPECT_EQ(pair.first,3);
    EXPECT_EQ(pair.second,4);
}

TEST(UtilsTest, twoPointers_ComputeSum2) {
    int v[] = {1, 1, 2, 3, 3, 49, 60, 62, 90, 1004, 8000};
    auto pair = twoPointers<int>(v, (sizeof(v)/sizeof(int)), conditionSum<int, 50>);
    EXPECT_EQ(pair.first, 1);
    EXPECT_EQ(pair.second, 49);
}

TEST(UtilsTest, slidingWindow_max) {
    std::vector<int> v {1, 1, 2, 3, 3, 49, 5, 2, 1, 0, 0};
    auto result = slidingWindow<int>(v.data(), v.size(), 3, SlidingWindowOp::MAX);
    EXPECT_EQ(result.value, 57);
    EXPECT_EQ(result.leftIndex, 4);
    EXPECT_EQ(result.rightIndex, 6);
}

}
