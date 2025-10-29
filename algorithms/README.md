# Algorithms

## Categories
- Big O notation
- sorting, searching, binary search
- divide and conquer
- dynamic programming and memoization
- greedy algorithms
- graph traversal, breadth and deep first
- recursion

# === Big O Notation ===
- binary search & recursive calls on data split by 1/2 - O(logN)
- merge sort - O(NlogN)
- looking for a square root of N
  - iterational - O(\sqrt(N))
  - by binary search - O(logN)
- checking N for a prime number - O(\sqrt(N))
- sum of all digits of N - O(logN), even O(log_10 N)
- generating all k-length combinations of N-element set - N^k
- generating all k-length combinations of N-element set without repetitions - N!/(N-k)!, especially N! for k=N length.
- total number of subsets - 2^N (including empty subset)
- generating all k-length unique tuples of N-element set - N!/((N-k)!k!)

# === SORTING ===

- _bubble sort O(N^2)_ - trivial but we don't use it, const memory O(1)
- _selection sort O(N^2)_ - trivial, don't use it, const memory O(1), find min and move to front, then find second min. etc.
- _merge sort (ONlogN)_ avg & worst case, varying memory
  - divide array in half, sort them and merge, recursively up to swapping two elements. merge method algorithm is heavy here
  - create the helper array of size N
  - use low, mid, high indexes
  - copy both halves into helper array
  - compare those elements, copy smaller from the left or right half, increase indexes
  - copy rest of the left side
- _quick sort O(NlogN)_ - provided that partition element is around median, worst case O(N^2), swapping elemets around the selected pivot point
- _radix sort O(kN)_ - exploiting finite number of bits, sorting digit wise

# === SEARCHING TREES ===

## Depth-First Search (graph) -> down the line to the bottom, use recursion and stack
Includes Pre-, In-, and Post-Order Traversals.

## Breadth-First Search (graph) -> level by level, use queue
When an array is used to store binary tree, its done by iterating all elements left-to-right, i.e.
- left child -> 2i + 1
- root -> i
- right child -> 2i + 2
Recommended only for perfect binary trees to avoid memory loss.

## Pre-Order Traversal (binary tree) -> visit, recurence(left), recurence(right)
Used for creating a copy of the tree and prefix notation of expression tree.

## In-Order Traversal (binary tree) -> recurence(left) until null -> return, visit, recurence(right) until null
Used in BSTs for returning values in ascending order.

## Post-Order Traversal (binary tree) -> recurence(left), recurence(right), visit
Used for tree deletion, post-fix notation of expression tree.

## Binary search - used in sorted arrays
  1. compare x to the midpoint, chose left half if x < midpoint
  2. continue recursively until x is found or subarray is empty
  - https://en.cppreference.com/w/cpp/algorithm/binary_search.html
  - std::binary_search from <algorithm>

# === OTHER SEARCHING ===

## Fast & Slow Pointer (Tortoise & Hare) ##
to detect cycles in the __linked List__

## Boyer-Moore's voting algorithm ##
to find majority element (>N/2 occurences), two variables: candidate + occurences, increase occurence if candidate == element, decrease if it is not, if drops to zero overwrite candidate

## Maximum possible sum of subarray ##
naive n^2 with all possible permutations

## Kadane's algorithm ##
iterating with extending window over next elements summing all, resetting window if negative sum is found https://www.geeksforgeeks.org/problems/kadanes-algorithm-1587115620/1

## missing number in [1,N] ##
compute the sum n(n+1)/2 and subtract sum of elements OR xor [1,N] with xor elements https://www.geeksforgeeks.org/dsa/find-the-missing-number/

## Trapping Rain Water ##
array of ints with building heights, https://www.geeksforgeeks.org/dsa/trapping-rain-water/

# === BIT MANIPULATION ===
- arithmetic right shift -> division by two, adding bit from the left side matching sign bit
- logical right shift -> adding bit zero from the left side
- x XOR 1 = ~x
- x XOR 0 =  x
- -K (base 10) == concat(1, 2^(N-1)-K)

# === MATH ===

## Prime numbers
- each positive integer can be decomposed into a product of prime numbers 2^N + 3^M + 5^O + 7^P...
- Hence, if y % x == 0 => x = 2^j0 * 3^j1 * ... && y = 2^k0 * 3*k1 * ... for all ji <= ki
- gcd(x,y) = 2^{min(j0,k0)} * 3^{min(j1,k1)} * ...
- lcm(x,y) = 2^{max(j0,k0)} * 3^{max(j1,k1)} * ...
- gcd(x,y)*lcm(x,y) = xy
- Sito Eratostenesa (Sieve of Eratostenes) - algorytm do wyznaczania liczb pierwszych w zadanym przedziale od 2 do N. Jeżeli N jest niepodzielna przez żadną z liczb pierwszych <=sqrt(N) to N jest pierwsza. Algorithm:
  - create list of all numbers from min (2) up to max
  - cross of all values divisable by min (2)
  - get next prime after min (3) == next not crossed of and cross of all numbers divisable by it through max
  - optimization: next cross of starting index equal to prime^2 because k*prime k<prime already ruled out
  - optimization: check primes only up to sqrt(max)
  - optimization: cross of through array with only odd numbers (even are cross off by division by prime 2)

## Probability

### Intersection
- P(A & B) = P(B given A)P(A) = P(A given B)P(B), e.g.
  probability of picking picking even number and between 1 and 5
  P(1<=number<=5 & number is even) =
    P(number is even given 1<=number<=5)P(1<=number<=5) = (2/5) * (1/2) = (1/5)

### Bayes Theorem
- P(A given B) = P(B given A)P(A)/P(B)

### Sum
- P(A or B) = P(A) + P(B) - P(A and B) e.g.
  P(even or <=5) = 50% + 50% - (1/5) = 80%

### Independence
  - A tells nothing about B
  P(A and B) = P(A)P(B) since P(B given A)=P(B)

### Mutual Exclusive
  - if one happens then other cannot
  - P(A or B) = P(A) + P(B) since P(A and B)=0
  - events cannot be both MUTEX and Independent if P>0

# === Optimizing & Solving Techniques

1. _Look for Bottlenecks_, Unnecesary work, Duplicated work
  Example: print all positive solutions to $ a^3+b^3=c^3+d^3 for a,b,c,d \in [1,1000] $

2. _Do It Yourself_, i.e. how would I do it if I had to do it manually
  Example problem: find permutations of a smaller string in the bigger string

3. _Simplify and Generalize_, i.e. do algorithm for simplified version of the problem, e.g. data type, then generalize to more complex.
  Example problem: ransom note from cut words -> change to cut characters and count frequency using hash table

4. _Base Case and Build_, i.e. solve problem for the first base case, e.g. n=1, then try to build up for n=2, n=3, and n=4 (should be enough) using prior solutions.
  Example problem: string permutations

5. _Data Structure brainstorm_, i.e. array? linked list? set? queue? binary tree? heap?
  Example problem: Randomly generated numbers stored in expanding array. How to track median? - two heaps, max and min, for two halves, lower and upper.

6. _Draw recursive calls as a tree_ to determine the runtime

# === DYNAMIC PROGRAMMING & MEMOIZATION ===

## Recursion with cached results
Example: fibonacci numbers
Naive runtime of fibonaci ~O(2^N), O(1.6^N). Optimal O(N) of time and space. Possible O(1) space.

# === Others ===

## Sweep Line Algorithm
Processing events on a timeline, in time order. To track minimum number of platforms for arriving/departure trains https://www.geeksforgeeks.org/dsa/minimum-number-platforms-required-railwaybus-station/#expected-approach-using-sweep-line-algorithm-on-time-and-o1-auxiliary-space

## Reversal Algorithm
To shift array right by K elements. Steps:
  1. Reverse last K elements, i.e. from idx[N-K] to idx[N-1]
  2. Reverse first N-K elements, i.e. from idx[0] to idx[N-K-1]
  3. Reverse entire array, i.e. from idx[0] to idx[N-1]
  https://www.geeksforgeeks.org/dsa/print-array-after-it-is-right-rotated-k-times/

## Manacher's Algorithm
To find the longest palindromic substring - https://www.geeksforgeeks.org/dsa/longest-palindromic-substring/#using-manachers-algorithm

# === Questions ===

1. Find in an unsorted array all pairs with diff=k
2. Recursive & iterative memoized Fibonacci

# Topics to focus on Interviews

## Hints

- double confirm with the recruiter (LOUDLY) I understand the problem
- Ask/propose example data
- Clarify the question -> Design a solution -> Write your code -> Test your code
