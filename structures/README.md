# === DATA STRUCTURES ===

## Sequence DSes to be accessed sequentially

---

### std::vector<T> - sequence, resizeable, std::vector<bool> - possibly space-optimized, also for bitset operations

  - Complexity:
    - Random access container O(1)
    - Insertion/removal at the end O(1)
    - Insertion/removal at the beginning O(n)

  - Getters/Accessors (random, front, back):
    - at() - with range checking
    - [] - without range checking
    - front() -> T&
    - back() -> T&
    - data() -> T*

  - Iterators:
    - begin() -> it (i.e. [0]) | end()
    - end() -> it (i.e. [N-1] .) [begin, ] end
    - rbegin()
    - rend()

  - Capacity:
    - empty() -> bool
    - size() -> size_t, same as std::distance(begin(), end())
    - max_size() -> size_t with max num of elements on system
    - reserve(size_t) - to reserve more (only) storage, to reduce shrink_to_fit()
    - capacity() -> size_t - num of elements that can be held in allocated storage
    - shrink_to_fit() - reduce memory usage

  - Modifiers:
    - clear()
    - insert(pos, {count}, &val|[firstIt lastIt])
    - emplace() - creates element in place
    - erase(pos|[firstIt lastIt) - removes elements at pos, returns iterator following the removed element
    - push_back(element)
    - append_range(container range)
    - void pop_back() - remove from back, no return
    - resize(count, {value})
    - swap(vector) - exchange elements and capacity with other

---

### std::array<T> - sequence, fixed-size

  - Getters/Accessors:
    - at()
    - []
    - front()
    - back()
    - data() -> T*

  - Capacity:
    - empty()
    - size()
    - max_size() ( equal to size())

  - Ops:
    - fill()
    - swap(other array) - exchange elements

---

### std::deque<T> - sequence, double-ended queue - fast insertion at both ends

  - indexed access requires 2 ptr dereferences
  - not stored contiguously
  - expansion is cheaper than vector at the cost of large minimal memory cost
  - Complexity:
    - random access O(1)
    - insertion/removal at the begining/end O(1)
    - insertion/removal in other places O(n)
  - Getters/accessors (same for vector except for data())
  - Iterators (same for vector)
  - Capacity (same for vector)
  - Modifiers (same for vector) plus: push_front, pop_front

---

### std::forward_list - sequence, singly-linked
  - more space efficient than list when no bidirectional iteration needed
  - fast insertion and removal anywhere
  - Accessors: front()
  - Capacity: empty(), max_size()
  - Modifiers: clear(), insert_after(), erase_after(), push_front(), pop_front(), resize(), swap()
  - Operations:
    - merge(fw_list) - merge two sorted list into one sorted list,  O(N+M) comparisons
    - splice_after() - transfer elements from another forward_list
    - remove, remove_if() - removes els satisfying criteria
    - reverse() - reverse the order
    - unique() - remove consecutive duplicates
    - sort() - sorts O(NlogN) comparisons

---

### std::list - sequence, double-linked
  - constant-time insertion and removal anywhere
  - fast random access not supported
  - bidirectional iteration
  - Accessors: front(), back()
  - Iterators: begin(), end(), rbegin(), rend()
  - Capacity: size(), max_size(), empty()
  - Modifiers: clear(), insert(), erase(), push_back(), pop_back(), push_front(), pop_front(), resize(), swap()
  - Operations: merge(), splice(), remove, remove_if(), unique(), sort(),

------

## Associative DSes to be quickly searched O(logN)

### set - unique keys, sorted by keys (implemented as red-black self balancing binary search tree)
- sorting with key comparison
- search, removal, insertion O(logN)
- Lookup: find()->it, count(), contains()->bool, lower_bound()->it, upper_bound()->it

### map - key-values, sorted by keys

### multiset - non-unique keys, (hashed/)sorted by keys

### multimap - non-unique key-values, (hashed/)sorted by keys

## Unordered associative DSes to be even quicker searched O(1) avg, O(n) worst

### unordered_set - unique keys, hashed by keys (implemented as red-black self balancing binary search tree)
- faster const access on hash (immutable) elements
- sorting with key comparison
- search, removal, insertion O(logN)
- Lookup: find()->it, count(), contains()->bool, lower_bound()->it, upper_bound()->it

### unordered_map - key-values, hashed by keys
- insert() - O(1)/O(N)
- searching - O(N)


### unordered_multiset - non-unique keys, (hashed/)sorted by keys

### unordered_multimap - non-unique key-values, (hashed/)sorted by keys

## Adaptors

### stack - a wrapper for underlying SequenceContainer providing LIFO access

### queue - a wrapper for underlying SequenceContainer providing FIFO access

### priority_queue - -//- providing constant time lookup of the largest element at the  cost of log insertion and extraction

### flat_set/map/multiset/multimap - with custom compare

## Trees and graphs

### Binary tree

- 2^N nodes where N is depth
- recursive function - usually  O(branches^depth)

### Binary Search Tree

#### AVL Tree
A self-balancing BST with left & right rotation, and a maitained balance factor -1 <= BF <=1
- right rotation Y.left := X.right && X.right := Y
- left rotation X.right := Y.left && Y.left := X

### Min/Max Heap (Binary Heap)

### Tries

For words, terminated with *

### Adjacency List graph

### Adjacency Matrix graph

# Topics to focus on Interviews

## Hints

- double confirm with the recruiter (LOUDLY) I understand the problem
- Ask/propose example data
- Clarify the question -> Design a solution -> Write your code -> Test your code
