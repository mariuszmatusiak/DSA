#include "dsa_structures.h"
#include "dsa_structures_nodes.h"
#include "dsa_utils.h"

#include <gtest/gtest.h>

#include <memory>
#include <cstdint>
#include <algorithm>
#include <string>
#include <vector> // https://en.cppreference.com/w/cpp/container/vector.html
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>

using std::string;
using std::vector;
using std::forward_list;
using std::list;
using std::stack;

using namespace DSA::Structures;
using DSA::Structures::SingleLinkedList;
using DSA::Structures::Node;
using DSA::Structures::SingleLinkedNode;
using DSA::Structures::DoubleLinkedNode;
using DSA::Utils::printContainer;
using DSA::Utils::printContainerInfo;
using DSA::Utils::printHeap;
using DSA::Utils::printMap;
using DSA::Utils::MAX;
using DSA::Utils::MIN;
using DSA::Utils::LOWEST;
using DSA::Utils::isIn;

namespace DSA::Structures::Tests {

class TestSuiteFixture : public testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

class ListTestSuite : public TestSuiteFixture {
};


TEST(StandardContainers, Vector) {
    vector<string> words{};
    ASSERT_EQ(words.size(), 0);
    words.push_back("ala"); // no push_front
    ASSERT_EQ(words[0], "ala");
    ASSERT_EQ(words.front(), "ala");
    ASSERT_EQ(words.back(), "ala");
}

// forward_list<string> list{};
// - .front()->T&; O(1)
// - .push_front("a"); O(1), .pop_front()->void; O(1)
// - .insert_after(pos,"") O(n), instead of push_back
// - emplace_after(pos,...) O(n)
// - erase_after(pos) O(1)
// - assign(count, ""), assign(first, last), assign{"a","b"} <- replacing content
// - clear()
// - resize()
// - swap(fw_list&)
// - merge(fw_list&, {Compare comp}) - used to merge two sorted lists into sorted list (merge sort useful)
// - splice_after(pos, fw_list& other, {firstIt}, {lastIt}) - transfer elements from other to this fw list and insert after pos
// - remove(element) - remove all elements equal to
// - remove_if(UnaryPred p) - remove all elements for which p predicate (lambda) returns true;
// - .reverse()
// - .unique() - remove consecutive duplicates
// - .sort() - NlogN
// - NO size() X, std::distance(begin(), end()) instead

TEST(StandardContainers, ForwardList) {
    forward_list<string> words{};
    ASSERT_EQ(words.empty(), true); // no words.size()

    words.push_front("ala"); // no push_back
    //ASSERT_EQ(words[0], "ala"); // no indexing
    ASSERT_EQ(words.front(), "ala");
    //ASSERT_EQ(words.back(), "ala"); // N/A

    words.push_front("ma");
    ASSERT_EQ(words.front(), "ma");

    words.insert_after(words.begin(), "kota");
    printContainer(words);
    words.pop_front();
    ASSERT_EQ(words.front(), "kota");

    words.clear();
    ASSERT_EQ(words.empty(), true);

    words.assign(5, "ala");
    printContainer(words);

    vector<string> v2 {"kot", "ma", "ale"};
    words.assign(v2.begin(), v2.end());
    printContainer(words);

    words.assign({"another", "data", "from", "initlist"});
    printContainer(words);

    forward_list<string> words2 {"words", "in", "words2"};
    printContainer(words2);

    words.swap(words2);
    printContainer(words);
    printContainer(words2);

    words2.remove_if([](string arg) { return isIn("anoth", arg); });
    printContainer(words2);
}

// std::list<type>
// - .front(), .begin() O(1)
// - .size() <- EXISTS vs fw_list
// - .insert{_range}()
// - .erase(frontIt, lastIt), .resize(), .remove(element), .remove_if
// - .push_back(), .push_front(), .pop_back(), .pop_front()
// - .emplace_back(), .emplace_front()

TEST(StandardContainers, List) {
    list<string> words{};
    ASSERT_EQ(words.empty(), true); // no words.size()
    words.push_front("ala"); // no push_back
    ASSERT_EQ(words.front(), "ala");
    ASSERT_EQ(words.back(), "ala"); // N/A

    words.push_back("ma");
    ASSERT_EQ(words.back(), "ma");

    words.insert(words.begin(), "kota");
    printContainer(words);

    words.pop_front();
    words.pop_back();
    ASSERT_EQ(words.front(), "ala");

    words.clear();
    ASSERT_EQ(words.empty(), true);

    words.assign(5, "ala");
    printContainer(words);

    vector<string> v2 {"kot", "ma", "ale"};
    words.assign(v2.begin(), v2.end());
    printContainer(words);

    words.assign({"another", "data", "from", "initlist"});
    printContainer(words);

    list<string> words2 {"words", "in", "words2"};
    printContainer(words2);
    words.swap(words2);
    printContainer(words);
    printContainer(words2);

    words2.remove_if([](string arg) { return isIn("anoth", arg); });
    printContainer(words2);
}

// std::deque<type>
//  - same as vector, except faster insertion and deletion at front and beginning,
//  - spreaded memory
TEST(StandardContainers, Deque) {
    std::deque<string> words{};
    words.push_back("back");
    words.push_front("front");
    EXPECT_EQ(words.front(), words[0]);
    EXPECT_EQ(words.back(), words[1]);
}

// std::set<type>
//  auto-sorted on insertion in ascending order, not indexed by numbers
//  - .insert(element);
//  - .erase(element);
//  - .clear()
//  - .size(), .empty()
TEST(StandardContainers, Set) {
    std::set<string, std::greater<string>> words {"ala", "ma", "kota", "a", "kot", "ma", "ale"}; //descending lexicographical order
    words.insert("a co na to azor");
    words.erase("a");
    printContainer(words);
}

// std::map<t1,t2>
//  - [], .insert({k,v});
//  - .erase(k);
//  - .clear()
//  - .size(), .empty()
//  - kv.first, kv.second
//  - it->first, it->second (using iterators)
TEST(StandardContainers, Map) {
    std::map<int, string> words {
        {10, "ala"},
        {9, "ma"},
        {8, "kota"}};
    words[7] = "a kot ma ale?";
    words.insert({6, "also works"});
    printMap(words);
}

// std::stack<type>
//  - .push(), .pop()
//  - .size(), .empty()
//  - .top(), uses std::deque
//  - NO iterators support
TEST(StandardContainers, Stack) {
    stack<string> pancakes; // {init, list, not, supported}
    stack<string> pierogies{};
    pancakes.push("oily");
    pancakes.push("small");
    pancakes.push("fried");
    pancakes.push("dry");
    pancakes.push("tasty");
    //printContainer(pancakes);
    EXPECT_EQ(pancakes.top(), "tasty");
    pancakes.top() = "cold";
    EXPECT_EQ(pancakes.top(), "cold");
    pancakes.pop();
    EXPECT_EQ(pancakes.top(), "dry");
    EXPECT_EQ(pancakes.size(), 4);
    EXPECT_EQ(pierogies.empty(), true);
}

// std::queue<type>
//  - front(), back(),
//  - push(), pop()
//  - empty(), size()
//  - No iterators support
TEST(StandardContainers, Queue) {
    std::queue<string> msgQueue{};
    msgQueue.push("event 1");
    msgQueue.push("event 2");
    EXPECT_EQ(msgQueue.front(), "event 1");
    EXPECT_EQ(msgQueue.back(), "event 2");
    msgQueue.pop();
    EXPECT_EQ(msgQueue.front(), "event 2");
    EXPECT_EQ(msgQueue.size(), 1);
}

// std::priority_queue - an auto-sorted queue
// Accessors:
//  - .top();
// Capacity:
//  - .empty(), .size();
// Modifiers:
//  - .push{_range}(), .emplace(), .pop(), .swap()
TEST(StandardContainers, PriorityQueue) {
    std::vector<int> v {3, 6, 1, 2, 9, 10, 12, 15, 3, 0};
    printContainer(v);
    std::priority_queue<int> pq{}; // descending, max pq
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq_reversed{}; // ascending
    for (auto element : v) {
        pq.push(element);
        pq_reversed.push(element);
    };
    printContainer(v);
    printHeap(pq);
    printHeap(pq_reversed);
}

TEST(StandardContainers, MaxHeap) {
    std::vector<int> v {5, 6, 12, 8, 7, 14, 19, 13, 12, 11};
    const size_t N {v.size()};
    printContainer(v);
    std::make_heap(v.begin(), v.end());
    printContainer(v); // after heapify
    // pop max from max heap
    std::pop_heap(v.begin(), v.end()); // swap max with last element in the vector and bubble element down for the heap invariant property (polling)
    printContainer(v);
    EXPECT_EQ(v.back(), 19);
    v.pop_back();
    printContainer(v);
    EXPECT_EQ(v.front(), 14);
    EXPECT_EQ(v.size(), N-1);
    // push value to max heap
    v.push_back(20);    // add a value to the end of vector
    printContainer(v);
    std::push_heap(v.begin(), v.end()); // bubble the value up
    EXPECT_EQ(v.front(), 20);
    EXPECT_EQ(v.size(), N);
    EXPECT_EQ(std::is_heap(v.begin(), v.end()), true);
    printContainer(v);
    // sort heap dropping the heap invariant property
    std::sort_heap(v.begin(), v.end());
    printContainer(v);
    EXPECT_EQ(std::is_heap(v.begin(), v.end()), false);
}

TEST(StandardContainers, MinHeap) {
    std::vector<int> v {5, 6, 12, 8, 7, 14, 19, 13, 12, 11};
    printContainer(v, true);
    std::make_heap(v.begin(), v.end(), std::greater<>{});
    printContainer(v, true); // after heapify
}

TEST(NodeSuite, InitListTest) {
    int i {10};
    char c {'b'};
    short s {256};
    double d {3.14};

    const int ci {-10};
    const char cc {'x'};
    const short cs {-512};
    const double cd {-.1};

    auto pi = std::make_shared<decltype(i)>(15); // shared_pointer to int
    auto pc = std::make_shared<decltype(c)>('z'); // shared_pointer to char

    Node<int> n1 {i};
    Node<char> n2 {c};
    Node<short> n3 {s};
    Node<double> n4 {d};
    Node<int> n6 {ci};
    Node<char> n7 {cc};
    Node<short> n8 {cs};
    Node<double> n9 {cd};
    Node<int> n11 {*pi};
    Node<char> n12 {*pc};
    Node<int> nint {1};
    Node<float> nflt {5.0f};
    Node<bool> nbol {true};

    EXPECT_EQ(n1.element, 10);
    EXPECT_EQ(n2.element, 'b');
    EXPECT_EQ(n3.element, 256);
    EXPECT_EQ(n4.element, 3.14);
}

TEST(NodeSuite, DefaultConstructorInitTest) {
    Node<int> node(5);
    EXPECT_EQ(node.element, 5);
    //Node<short> emptyNode(); // shouldn't compile
    //Node<double> otherEmptyNode{}; // also shouldn't compile
}

TEST(NodeSuite, CopyConstructorInitTest) {
    Node<int> node(5);
    Node<int> nodecopy(node);
    EXPECT_EQ(node.element, 5);
    EXPECT_EQ(nodecopy.element, 5);
}

template<typename N>
N getNodeCopy(N node) {
    return node;
}

TEST(NodeSuite, MoveConstructorInitTest) {
    Node<int> node(5);
    Node<int> nodemoved{getNodeCopy(node)}; // TODO still copy ctor is called, {} or () no difference
    EXPECT_EQ(node.element, 5);
    EXPECT_EQ(nodemoved.element, 5);
}

TEST(NodeSuite, CopyAssignmentOperatorTest) {
    Node<int> node{5};
    Node<int> node2{10};
    // node2 = node; // compiler fail due to explicitly copy assignment operetor deleted
    // EXPECT_EQ(node2.element, 5);
}

/**
TEST(NodeSuite, BaseStringTest) {
    GTEST_SKIP(); // skips execution but still compiles
    string str {"huehue"};
    const string cstr {"huahua"};
    auto pstr = std::make_shared<decltype(str)>("hihi");
    Node<string> n5 (str);
    Node<string> n10 {cstr};
    Node<string> n13 {*pstr};
    string s {"string node"};
    Node<string> nstd {s};
    Node<const char *> nchr {"char node"};
    EXPECT_EQ(str, "huehue");
}
*/

TEST(SingleLinkedNodeSuite, InitListTest) {
    int i {10};
    char c {'b'};
    short s {256};
    double d {3.14};

    const int ci {-10};
    const char cc {'x'};
    const short cs {-512};
    const double cd {-.1};

    auto pi = std::make_shared<decltype(i)>(15); // shared_pointer to int
    auto pc = std::make_shared<decltype(c)>('z'); // shared_pointer to char

    SingleLinkedNode<int> n1 {i};
    SingleLinkedNode<char> n2 {c};
    SingleLinkedNode<short> n3 {s};
    SingleLinkedNode<double> n4 {d};
    SingleLinkedNode<int> n6 {ci};
    SingleLinkedNode<char> n7 {cc};
    SingleLinkedNode<short> n8 {cs};
    SingleLinkedNode<double> n9 {cd};
    SingleLinkedNode<int> n11 {*pi};
    SingleLinkedNode<char> n12 {*pc};
    SingleLinkedNode<int> nint {1};
    SingleLinkedNode<float> nflt {5.0f};
    SingleLinkedNode<bool> nbol {true};

    EXPECT_EQ(n1.element, 10);
    EXPECT_EQ(n2.element, 'b');
    EXPECT_EQ(n3.element, 256);
    EXPECT_EQ(n4.element, 3.14);
}

TEST(SingleLinkedNodeSuite, DefaultConstructorInitTest) {
    SingleLinkedNode<int> node(5);
    EXPECT_EQ(node.element, 5);
    //SingleLinkedNode<int> node2;
}

TEST(SingleLinkedNodeSuite, CopyConstructorInitTest) {
    SingleLinkedNode<int> node(5);
    SingleLinkedNode<int> nodecopy(node);
    EXPECT_EQ(node.element, 5);
    EXPECT_EQ(nodecopy.element, 5);
}

TEST(SingleLinkedNodeSuite, MoveConstructorInitTest) {
    SingleLinkedNode<int> node(5);
    SingleLinkedNode<int> nodemoved{getNodeCopy(node)}; // TODO still copy ctor is called, {} or () no difference
    EXPECT_EQ(node.element, 5);
    EXPECT_EQ(nodemoved.element, 5);
}

TEST(DoubleLinkedNodeSuite, InitListTest) {
    int i {10};
    char c {'b'};
    short s {256};
    double d {3.14};

    const int ci {-10};
    const char cc {'x'};
    const short cs {-512};
    const double cd {-.1};

    auto pi = std::make_shared<decltype(i)>(15); // shared_pointer to int
    auto pc = std::make_shared<decltype(c)>('z'); // shared_pointer to char

    DoubleLinkedNode<int> n1 {i};
    DoubleLinkedNode<char> n2 {c};
    DoubleLinkedNode<short> n3 {s};
    DoubleLinkedNode<double> n4 {d};
    DoubleLinkedNode<int> n6 {ci};
    DoubleLinkedNode<char> n7 {cc};
    DoubleLinkedNode<short> n8 {cs};
    DoubleLinkedNode<double> n9 {cd};
    DoubleLinkedNode<int> n11 {*pi};
    DoubleLinkedNode<char> n12 {*pc};
    DoubleLinkedNode<int> nint {1};
    DoubleLinkedNode<float> nflt {5.0f};
    DoubleLinkedNode<bool> nbol {true};

    EXPECT_EQ(n1.element, 10);
    EXPECT_EQ(n2.element, 'b');
    EXPECT_EQ(n3.element, 256);
    EXPECT_EQ(n4.element, 3.14);
}

TEST(DoubleLinkedNodeSuite, DefaultConstructorInitTest) {
    DoubleLinkedNode<int> node(5);
    EXPECT_EQ(node.element, 5);
    //DoubleLinkedNode<int> node2;
}

TEST(DoubleLinkedNodeSuite, CopyConstructorInitTest) {
    DoubleLinkedNode<int> node(5);
    DoubleLinkedNode<int> nodecopy(node);
    EXPECT_EQ(node.element, 5);
    EXPECT_EQ(nodecopy.element, 5);
}

TEST(DoubleLinkedNodeSuite, MoveConstructorInitTest) {
    DoubleLinkedNode<int> node(5);
    DoubleLinkedNode<int> nodemoved{getNodeCopy(node)}; // TODO still copy ctor is called, {} or () no difference
    EXPECT_EQ(node.element, 5);
    EXPECT_EQ(nodemoved.element, 5);
}

TEST(ListSuite, Create) {
    SingleLinkedList<int> myList;
    EXPECT_EQ(myList.isEmpty(), true);
}

TEST(ListSuite, Insert) {
    SingleLinkedList<int> myList;
    EXPECT_EQ(myList.isEmpty(), true);
    // myList.print();
    int * heapelement = new int;
    //myList.push_back(5);
    //myList.print();
    delete heapelement;
}

TEST(ListSuite, InPlaceReversal) {

}

TEST(ListSuite, FastAndSlowPtr) {

}

TEST(QueueSuite, FIFO) {

}

TEST(StackSuite, MonotonicStack) {

}

TEST(HeapSuite, MinHeap) {

}

TEST(HeapSuite, MaxHeap) {

}


TEST(BinaryTreeSuite, PreOrderTraversal) {

}

TEST(BinaryTreeSuite, InOrderTraversal) {

}

TEST(BinaryTreeSuite, PostOrderTraversal) {

}

TEST(BinaryTreeSuite, DepthFirstSearch) {

}

TEST(BinaryTreeSuite, BreadthFirstSearch) {

}

TEST(BinaryTreeSuite, Backtracking) {

}

}
