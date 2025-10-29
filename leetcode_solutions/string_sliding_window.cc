#include <unordered_map>
#include <unordered_set>
#include <limits>    // for std::numeric_limits
#include <algorithm> // for std::min

// the max sliding window size can be narrowed down 
// to the max range of unique characters which can be
// stored by the char type, every string longer than
// MAX_K_SIZE will have duplicates
constexpr size_t MAX_K_SIZE { std::numeric_limits<char>::max() - std::numeric_limits<char>::min() + 1u };

class StringSlidingWindow {
private:
    //std::deque<T> window;
    std::list<char> window;
    std::unordered_map<char, size_t> charsIndices; // for quick ~O(1) lookups
    const std::string& s;
    size_t maxWindowLength;
    size_t rightIdx;
    size_t leftIdx;

    inline void updateMaxWindowLength(size_t arg) {
        if (arg > maxWindowLength) { maxWindowLength = arg; }
    }

public:
    StringSlidingWindow() = delete;
    StringSlidingWindow(const std::string& str) : s(str), window{}, leftIdx{0}, rightIdx{0}, charsIndices{} {
        charsIndices.reserve(MAX_K_SIZE); // reserve memory for up to MAX_K_SIZE unique elements - potential optimizations, runtime to be validated
        window.push_back(s.at(rightIdx)); // initialize by adding the first character
        charsIndices.insert({s.at(rightIdx), rightIdx}); // ~O(1) amortized
        updateMaxWindowLength(window.size()); 
    }

    void increaseSize() {
        if ((rightIdx + 1) < MAX_K_SIZE) {
            char nextElement[rightIdx + 1];
            // check for duplicates first
            if (auto elementIt = charsIndices.find(nextElement); elementIt != charsIndices.end()) {
                // duplicate exists, reset the sliding window size, and shift the left index to the next position after the duplicate
                leftIdx = elementIt->second + 1u;
                window.pop_front()

            } else {
                // no duplicate found, proceed with extending the sliding window size
                ++rightIdx;
                window.push_back(s.at(rightIdx)); // initialize by adding the first character
                charsIndices.insert({s.at(rightIdx), rightIdx}); // ~O(1) amortized
                updateMaxWindowLength(window.size()); 
            }

        }
    }

    void slideWindowRight() {

    }

    int getWindowLength() const {
        return static_cast<int>(windowLength);
    }
};

class Solution {
private: 
    int hasDuplicate(const std::string& str) {
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

    inline std::string getNextKLongSubstring(const std::string& str, const size_t K, const size_t pos) {
        const size_t count { ( pos <= (str.size() - K) ) ? K : ( str.size() - pos ) };
        return str.substr(pos, count);
    }

    /**
     * Quite good overall, but too long for the 987/988 test case.
     * Needs further optimizations.
     */
    inline int slidingWindowSizeDecreasingApproach(const string& s) {
        size_t N { s.size() };
        if (N < 2) { return static_cast<int>(N); }
        size_t longestSubstringSize {1}; // the worst-case answer for non-empty strings, there's no need to generate byte-long substrings
        bool longerSubstringFound {false};
        for (size_t slidingWindowSize = std::min(N, MAX_K_SIZE); (slidingWindowSize > 1 && !longerSubstringFound); --slidingWindowSize) {
            for (size_t idx = 0u; (idx + slidingWindowSize) <= N; ++idx) {
                std::string substring {getNextKLongSubstring(s, slidingWindowSize, idx)};
                if (!hasDuplicate(substring)) { // can also declare sliding window as deque/double linked list and use pop_front and push_back
                    // std::cout << "Longest substring: " << substring << std::endl;
                    longestSubstringSize = slidingWindowSize;
                    longerSubstringFound = true; // flag to break outer loop
                    break;
                }
            }
        }
        return static_cast<int>(longestSubstringSize);
    }

    inline int slidingWindowListApproach(const string& s) {
        size_t N { s.size() };
        if (N < 2) { return static_cast<int>(N); }
        size_t longestSubstringSize {1};

        return static_cast<int>(longestSubstringSize);
    }

public:
    int lengthOfLongestSubstring(const string& s) {
        return slidingWindowSizeDecreasingApproach(s);
    }
};