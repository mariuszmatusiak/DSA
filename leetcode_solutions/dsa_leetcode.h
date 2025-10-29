#ifndef DSA_LEETCODE_H
#define DSA_LEETCODE_H

#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

#define ENABLE_LOGS 1

using std::vector;
using std::string;
using std::unordered_map;
using HashSet = std::unordered_set<int>;

namespace DSA::LeetCode {

class Solution {
private:
    // Utils
    static void print(vector<int>& nums);
    static void shiftElementsLeft(vector<int>& nums, const size_t startIdx);
    int inPlaceShiftApproach(vector<int>& nums);
    int naiveVectorApproach(vector<int>& nums);
    void shiftVectorWithReversalAlgorithm(); // TODO
    void shiftVectorByOneElement(vector<int>& nums, const bool right = true);
    void shiftVectorKTimesNaive(vector<int>& nums, const int k, const bool right = true);
    void shiftVectorTwoPointers(vector<int>& nums, const int k, const bool right = true);
    void shiftVectorWithExtraSpace(vector<int>& nums, const int k, const bool right = true);
    void shiftVectorKTimes(vector<int>& nums, const int k, const bool right = true);
    int maxProfitNaive(vector<int>& prices);
    int maxProfitKadane(vector<int>& prices);
    inline char isAlnum (const char arg) {
        if ((arg >= '0' && arg <= '9') ||
            (arg >= 'a' && arg <= 'z')) { // also std::isalnum from <cctype> or <locale>
            return arg;
        } else if (arg >= 'A' && arg <= 'Z') { // to lowercase
            constexpr size_t offset {('a' - 'A')};
            return arg + offset;
        } else {
            return 0;
    }
}
public:

    // 26. Remove Duplicates from Sorted Array
    int removeDuplicates(vector<int>& nums);

    // 274. H-Index
    int hIndex(vector<int>& citations);

    // Google. Find the smallest subarray that needs to be sorted to make the whole array sorted. Return the starting and ending indices.
    std::pair<int, int> findSubarrayToSort(const int * arr, const size_t length);

    // 80. Remove Duplicates from Sorted Array II
    int removeDuplicates2(vector<int>& nums);

    // 169. Majority Element
    int majorityElement(vector<int>& nums);

    // 189. Rotate Array
    void rotate(vector<int>& nums, int k);

    // 121. Best Time to Buy and Sell Stock
    int maxProfit(vector<int>& prices);

    // 125. Valid Palindrome
    bool isPalindrome(string s);

    // 2154. Keep Multiplying Found Values by Two
    int findFinalValue(vector<int>& nums, int original);
};

}

#endif // DSA_LEETCODE_H
