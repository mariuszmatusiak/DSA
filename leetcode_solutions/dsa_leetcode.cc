#include "dsa_leetcode.h"
#include "dsa_utils.h"
#include <algorithm>

namespace DSA::LeetCode {

int Solution::removeDuplicates(vector<int>& nums)
{
    const size_t numsSize {nums.size()};
    if (numsSize < 2u)
        return numsSize; // nothing to do, exit.
    int nextUniqueEl = nums.front();  // can be done also using two pointers, without the nextUniqueEl variable
    for (auto it = (nums.begin() + 1); it != nums.end(); /* DO NOT increase it here */) {
        if (*it != nextUniqueEl)
        {
            nextUniqueEl = *it;
            ++it;
        } else {
            it = nums.erase(it); // remove the same element, and get the iterator to the next element
        }
    }
    return nums.size();
}

int Solution::hIndex(vector<int>& citations) {
    int hIndex {0};
    std::map<int, int> citationsCounter {}; /* <numberOfCitationsI, numberOfPapersNWithCitationsI> */
    for (int i = 0; i < citations.size(); ++i) // O(n)
    {
        if (citations[i] <= 0)
            continue; // ignore zeros and other potentially negative values
        citationsCounter[citations[i]]++; // first initialize with zero if key doesn't exist, next increase number of papers by 1, ~O(1), end up with sorted map
    }
    // now iterate backwards (in descending order and count max H-index)
    int totalPapersWithMinimumCitations {0};

    for (auto it = citationsCounter.rbegin(); it != citationsCounter.rend(); ++it)
    {
        totalPapersWithMinimumCitations += it->second;
        if (totalPapersWithMinimumCitations >= it->first)
        {
            hIndex = it->first;
            break;
        }
    }
    return hIndex;
}

// Google
// Find the smallest subarray that needs to be sorted to make the whole array sorted.
// Return the starting and ending indices.
// {0, 1, 2, 5, 4, 6, 3, 8, 9, 10}
std::pair<int, int> Solution::findSubarrayToSort(const int * arr, const size_t length)
{
    int leftIdx {-1};
    int rightIdx {-1};
    std::pair<int, int> result (leftIdx, rightIdx);
    for (size_t i = 1; i < length; ++i)
    {
        if (arr[i] < arr[i-1])
        {
            leftIdx = i - 1; // inflection point
            break;
        }
    }
    if (leftIdx < 0) { return result; } // no incorrect subarray, we can return
    for (rightIdx = length - 1; rightIdx > leftIdx; --rightIdx)
    {
        if (arr[rightIdx] < arr[leftIdx] || arr[rightIdx-1] > arr[rightIdx])
        {
            break;
        }
    }
    result.first = leftIdx;
    result.second = rightIdx;
    return result;
}

int Solution::naiveVectorApproach(vector<int>& nums) {
    size_t counter {0};
    int nextUniqueElement {std::numeric_limits<int>::min()};
    // size_t noOfSwaps {0};
    for (auto it = nums.begin(); it != nums.end(); )
    {
        int currentElement = *it;
        if (currentElement != nextUniqueElement)
        {
            counter = 1; // reset counter and assign unique element
            nextUniqueElement = currentElement;
            ++it;
            continue;   // then jump to the next element immediately
        }
        ++counter; // same element as before, increase the counter
        if (counter >= 3)
        {
            it = nums.erase(it); // remove the current element from position it
            // and add to the end of the array
            // nums.push_back(std::numeric_limits<int>::min());
            //++it;
            // ++noOfSwaps;
        } else {
            ++it;
        }
    }
    return (nums.size() /* - noOfSwaps*/ );
}

int Solution::inPlaceShiftApproach(vector<int>& nums) {
    const size_t N = nums.size();
    if (N < 3) {
        return N; // return immediately for the small array
    }
    size_t noOfSwaps {0};
    for (size_t leftIndex = 2u; leftIndex < (N - noOfSwaps); )
    {
        Solution::print(nums);
#if ENABLE_LOGS
        std::cout << "Left index " << leftIndex << ", swaps " << noOfSwaps << std::endl;
#endif
        // condition must be defined this way, a == b == c doesn't work
        if ((nums[leftIndex] == nums[leftIndex-1u]) && (nums[leftIndex-1u] == nums[leftIndex-2u]))
        {
            Solution::shiftElementsLeft(nums, leftIndex);
            ++noOfSwaps;
#if ENABLE_LOGS
            std::cout << "Shifting elements..." << std::endl;
#endif
        } else
        {
            ++leftIndex;
#if ENABLE_LOGS
            std::cout << "Increasing index..." << std::endl;
#endif
        }
    }
#if ENABLE_LOGS
    std::cout << "k = " << (N - noOfSwaps) << std::endl;
#endif
    return (N - noOfSwaps);
}

/**
* Critical assumptions:
* - in-place
* - O(1) space complexity
* - non-decreasing
* - only first k elements of the result matter
* - avoid resizing array
* - do not create another array (hash map idea abandoned)
* - each element at most twice
*/
int Solution::removeDuplicates2(vector<int>& nums) {
    return inPlaceShiftApproach(nums);
}

// naive brute force solution - iterate with counting occurences in hash map
// optimized solution - fixed-size hash map with break
// Other suggested approach - Boyer-Moore's voting algorithm
int Solution::majorityElement(vector<int>& nums) {
    const size_t N = nums.size();
    int result = nums[0]; // always for N <= 2
    if (N <= 2) {
        return result;
    }
    const size_t majorityCounter = (N >> 1) + 1u;
    unordered_map<int, size_t> elementOccurence;
    elementOccurence.reserve(majorityCounter); // up to ceil(N/2) keys space is needed considering all different elements, except for majority element
    for (auto it = nums.begin(); it != nums.end(); ++it)
    {
        if (++elementOccurence[*it] >= majorityCounter) {
            result = *it;
            break;
        }
    }
    return result;
}

// === UTILS METHODS ===

void Solution::print(vector<int>& nums) { // static keyword in declaration only
#if ENABLE_LOGS
    std::cout << "[ ";
    for (auto& e : nums)
        std::cout << e << ", ";
    std::cout << "]" << std::endl;
#endif // ENABLE_LOGS
}

void Solution::shiftElementsLeft(vector<int>& nums, const size_t startIdx) {
    const size_t lastIdx = nums.size() - 1;
    int swappedElement = nums[startIdx];
    for (size_t i = startIdx; i < lastIdx; ++i) {
        nums[i] = nums[i+1];
    }
    nums[lastIdx] = swappedElement;
}

void Solution::shiftVectorByOneElement(vector<int>& nums, const bool right) {
    int tmp;
    const size_t lastIdx = nums.size() - 1;
    if (right) {
        tmp = nums[lastIdx];
        for (size_t k = lastIdx; k > 0; --k)
        {
            nums[k] = nums[k-1];
        }
        nums[0] = tmp;
    } else { // left
        tmp = nums[0];
        for (size_t k = 0; k < lastIdx; ++k)
        {
            nums[k] = nums[k+1];
        }
        nums[lastIdx] = tmp;
    }
}

void Solution::shiftVectorKTimesNaive(vector<int>& nums, const int k, const bool right) {
    const size_t N = nums.size();
    const int k_actual = k % N;
    if (k_actual == 0) {
        return;
    }
    if (k_actual <= (N >> 1)) {
        // shift in the right direction
        for (int i = 0; i < k_actual; ++i) {
            shiftVectorByOneElement(nums, right);
        }
    } else {
        // shift in the opposite direction (faster)
        for (int i = 0; i < N - k_actual; ++i) {
            shiftVectorByOneElement(nums, !right);
        }
    }
}

// to be fixed
void Solution::shiftVectorTwoPointers(vector<int>& nums, const int k, const bool right)
{
    const size_t lastIndex = nums.size() - 1; // 6
    const size_t firstIndex = 0;
    if (right) {
        for (int i = 0; i < k; ++i) {
            int moveToIndex = lastIndex - i; // for 6, 5, 4
            int tmp = nums[moveToIndex]; // [6] = 7
            int moveFromIndex = moveToIndex - k; // 3, 2, 1
            while (moveFromIndex >= firstIndex) {
                nums[moveToIndex] = nums[moveFromIndex]; // nums[6]<-nums[3]; nums[3]<-nums[0]
                moveToIndex = moveFromIndex; // mTI<-3, mTI<-0
                moveFromIndex -= k; // mFI<-3-3=0, mFI<-0-3=-3 +7? == 4
            }
            nums[moveToIndex] = tmp;
        }
    } else {
        for (int i = 0; i < k; ++i) {
            int moveToIndex = firstIndex + i;
            int tmp = nums[moveToIndex];
            int moveFromIndex = moveToIndex + k;
            while (moveFromIndex <= lastIndex) {
                nums[moveToIndex] = nums[moveFromIndex];
                moveToIndex = moveFromIndex;
                moveFromIndex += k;
            }
            nums[moveToIndex] = tmp;
        }
    }
}

void Solution::shiftVectorWithExtraSpace(vector<int>& nums, const int k, const bool right)
{
    // move last k elements to another vector
    vector<int> tmpVector {};
    auto nums_begin_it = (right) ? (nums.begin() + (nums.size() - k)) : nums.begin();
    auto nums_end_it   = (right) ? (nums.end()) : (nums.begin() + k);
    // cout << "Init\n";
    // print(nums);
    // print(tmpVector);
    std::move(nums_begin_it, nums_end_it, std::back_inserter(tmpVector));
    // cout << "Moved\n";
    // print(nums);
    // print(tmpVector);
    // shift
    const int lastIndex = nums.size() - 1;
    const int sliceIndex = nums.size() - k;
    const int firstIndex = 0;
    int moveToIndex = (right) ? lastIndex : firstIndex;
    int moveFromIndex = (right) ? (moveToIndex - k) : (moveToIndex + k);
    // cout << moveToIndex << endl;
    // [3, 0]
    while (((right) ? (moveFromIndex >= firstIndex) : (moveFromIndex <= lastIndex)))
    {
        // cout << nums[moveFromIndex] << " -> " << nums[moveToIndex] << endl;
        nums[moveToIndex] = nums[moveFromIndex];
        // print(nums);
        if (right) {
            --moveToIndex;
            --moveFromIndex;
        } else {
            ++moveToIndex;
            ++moveFromIndex;
        }
    }
    // cout << "Shifted\n";
    // print(nums);
    // print(tmpVector);
    for (int tmpVindex = 0, numsIndex = (right) ? firstIndex : sliceIndex; tmpVindex < k; ++tmpVindex, ++numsIndex) {
        nums[numsIndex] = std::move(tmpVector[tmpVindex]);
    }
    // cout << "Restored\n";
    // print(nums);
    // print(tmpVector);
}

void Solution::shiftVectorKTimes(vector<int>& nums, const int k, const bool right) {
    const int N = nums.size();
    // skip all redundant shifts, i.e. k > N
    const int k_actual = k % N;
    // return immediately if k == M * N
    if (k_actual == 0) {
        return;
    }
    if (k_actual <= (N >> 1)) {
        // shift in the right direction
        shiftVectorWithExtraSpace(nums, k_actual, right);
    } else {
        shiftVectorWithExtraSpace(nums, N - k_actual, !right);
    }
}

void Solution::rotate(vector<int>& nums, int k) {
    //shiftVectorKTimesNaive(nums, k, true);
    shiftVectorKTimes(nums, k, true);
}

int Solution::maxProfitNaive(vector<int>& prices){
    if (prices.size() < 2) return 0;
    size_t minIndex {0};
    size_t maxIndex {0};
    int min {0xFFFF};
    int max {0xFFFF};
    int maxProfit {max - min};
    // find minimum
    for (size_t day = 0; day < prices.size(); ++day)
    {
        if (prices[day] < min) {
            min = prices[day];
            for (size_t nextDay = day + 1; nextDay < prices.size(); ++nextDay)
            {
                if ((prices[nextDay] - prices[day]) > maxProfit) {
                    maxProfit = (prices[nextDay] - prices[day]);
                    minIndex = day;
                    maxIndex = nextDay;
                }
            }

        }
    }
    int resultProfit = maxProfit > 0 ? maxProfit : 0;
    //std::cout << "Buy on " << minIndex << ", sell on " << maxIndex << ", profit: " << resultProfit;
    return resultProfit;
}

int Solution::maxProfitKadane(vector<int>& prices)
{
    int maxProfit {0};
    int min {prices[0]};
    size_t maxIndex {0};
    size_t minIndex {0};
    size_t minIndexProposal {0};
    if (prices.size() < 2) return maxProfit;
    for (size_t day = 1; day < prices.size(); ++day) {
        if (prices[day] < min) {
            min = prices[day];
            minIndexProposal = min;
        }
        if ((prices[day] - min) > maxProfit) {
            maxProfit = prices[day] - min;
            maxIndex = day;
            minIndex = minIndexProposal;
        }
    }
    //std::cout << "Buy on " << minIndex << ", sell on " << maxIndex << ", profit: " << maxProfit;
    return maxProfit;
}

int Solution::maxProfit(vector<int>& prices) {
    return maxProfitKadane(prices);
}

bool Solution::isPalindrome(string s) {
    size_t leftIdx {0};
    size_t rightIdx {s.size()-1};

    while (leftIdx < rightIdx)
    {
        const char leftX  { isAlnum(s[leftIdx]) };
        const char rightX { isAlnum(s[rightIdx]) };
        if (!leftX) {
            ++leftIdx; // skip left nonalphanumeric char
            continue;
        }
        if (!rightX) {
            --rightIdx; // skip right nonalphanumeric char
            continue;
        }
        if (leftX != rightX) {
            return false;
        }
        ++leftIdx;
        --rightIdx;
    }
    return true;
}

int Solution::findFinalValue(vector<int>& nums, int original) {
    HashSet numSet(nums.begin(), nums.end());
    while(numSet.contains(original)) { original <<= 1; }
    return original;
}

} // namespace DSA::LeetCode
