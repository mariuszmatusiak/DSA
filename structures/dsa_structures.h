#ifndef DSA_STRUCTURES_H
#define DSA_STRUCTURES_H

#include "dsa_structures_nodes.h"
#include "dsa_utils.h"

#include <iostream>
#include <concepts> // for adding constraing and limitations to templates
#include <string>
#include <utility> // for std::move(arg) - tells assignee copy/assignment operator to treats arg as a movable rvalue
#include <vector>
#include <forward_list>
#include <utility>
#include <exception>
#include <queue>
#include <algorithm> // for std::make_heap()
#include <memory> // for std::shared_ptr, std::unique_ptr, std::weak_ptr

using DSA::Utils::formatPtr;
using std::shared_ptr;

namespace DSA::Structures {

class NoElementFoundException : public std::exception {
private:
    std::string message{};
public:
    NoElementFoundException(std::string errorMessage) : message{errorMessage} {};
    const char * what() const noexcept override { return message.c_str(); }
};

template<typename T>
class DataStructure {
protected:
    bool useStandard {false};
public:
    virtual size_t size() const = 0;
    virtual bool isEmpty() const = 0;
    virtual const T& peek() const = 0;
    virtual bool hasElement(const T& element) const = 0;
    virtual const T& removeElement(const T& element) = 0;
    virtual void print() const = 0;
    virtual void clear() = 0;
    virtual ~DataStructure() {};
};

template<typename T>
class SingleLinkedList : public DataStructure<T> {
private:
    size_t cachedSize {};
    const bool cached {false};
protected:
    shared_ptr<SingleLinkedNode<T>> head {nullptr};
public:
    SingleLinkedList() : cached(false) {}
    SingleLinkedList(const bool useCache) : cached(useCache) {}
    void append(const T& element) { push_back(element); }

    // O(1)
    bool isEmpty() const override { return (head == nullptr); }

    // O(1)
    const T& peek() const override {
        if (isEmpty())
            throw NoElementFoundException("SingleLinkedList::peek() error: the list is empty!");
        return head->element;
    }

    // O(1) - O(n)
    size_t size() const override {
        if (cached) return cachedSize;
        else {
            size_t size {0};
            shared_ptr<SingleLinkedNode<T>> node {head};
            while (node != nullptr) {
                ++size;
                node = node->next_right;
            }
            return size;
        }
    }

    // O(n)
    bool hasElement(const T& element) const override {
        if (isEmpty()) return false;
        else {
            shared_ptr<SingleLinkedNode<T>> node {head};
            while (node != nullptr) {
                if (node->element == element) return true;
                node = node->next_right;
            }
            return false;
        }
    }

    // O(n)
    const T& removeElement(const T& element) override {
        shared_ptr<SingleLinkedNode<T>> node {head};
        while (node != nullptr) {
            shared_ptr<SingleLinkedNode<T>> nextNode {node->next_right};
            if (node->element == element) {
                const T& removedElement = node->element;
                // delete node;
                --cachedSize;
                node = nextNode; // TODO test this
                return removedElement;
            }
            node = node->next_right;
        }
        throw NoElementFoundException("SingleLinkedList::removeElement() error: element not found!");
    }

    void print() const override {
        shared_ptr<SingleLinkedNode<T>> node {head};
        std::cout << std::format("SingleLinkedList {:p} content:", formatPtr(*this)) << std::endl;
        while (node != nullptr) {
            std::cout << node->str() << std::endl;
            node = node->next_right;
        }
    }

    void clear() override {
        while (head != nullptr) {
            pop_back();
        }
    }

    // MANDATORY
    virtual void prepend(const T& element) { push_front(element); }

    virtual void push_front(const T& element) {
    }

    virtual const T& pop_front() {}

    // ADDITIONAL

    // O(1) - O(n)
    virtual void push_back(const T& element) {
        shared_ptr<SingleLinkedNode<T>> * ptrToNodePtr {&head};
        while (*ptrToNodePtr != nullptr) {
            ptrToNodePtr = &((*ptrToNodePtr)->next_right);
        }
        // TODO fix *ptrToNodePtr = std::make_shared(SingleLinkedNode<T>(element));
        ++cachedSize;
    }

    virtual const T& pop_back() {
        peek(); // check if list is empty
        shared_ptr<SingleLinkedNode<T>> node {head};
        while (node->next_right != nullptr) {
            node = node->next_right;
        }
        const T& poppedElement = node->element;
        // delete node;
        --cachedSize;
        return poppedElement;
    }

    ~SingleLinkedList() override {
        clear();
    }
};


template<typename T>
class LinkedList : public SingleLinkedList<T> {
private:
    using SingleLinkedList<T>::head;
    shared_ptr<DoubleLinkedNode<T>> tail {nullptr};
public:
    LinkedList() : SingleLinkedList<T>() {}
    LinkedList(const bool useCache) : SingleLinkedList<T>(useCache) {}

    ~LinkedList() override {}
};

template<typename T>
class Stack : public DataStructure<T> {
private:
    std::stack<T> standardStack {};
    bool useStandard {false};
public:
    // push, pop, size, empty, top
};

class Queue {

};

template <typename T>
class PriorityQueue : public DataStructure<T> {
private:
    std::priority_queue<T> standardPQ {}; // push, pop, top, empty, size
    bool useStandard {false};

};

// Heap - a non-cycle, tree-based DS satisfying the *heap invariant* property, i.e.
//  - for Max Heap - parent node is greater than child nodes, for all nodes
//  - for Min Heap - parent node is smaller than child nodes, for all nodes
// Providing constant time lookup of the largest element at the  cost of log insertion and extraction.
// Usage: Dijkstra's shortest path; next best/worst element; Huffman coding (data compression); Best First Search algorithms; Minimum Spanning Tree algorithms;

template <typename T>
class Heap : public DataStructure<T>  {
private:
    // peek/top, pushAndSort, pop, emplace
    std::vector<T> standardHeap;
public:
    Heap(/*init list*/) {
        //copy to standardHeap
        std::make_heap(standardHeap.first(), standardHeap.last());
    }
};

template <typename T>
class BinaryTree : public DataStructure<T>  {

};

template <typename T>
class BinarySearchTree : public DataStructure<T>  {

};

template<typename K, typename V>
class HashMap : public DataStructure<K>  {
private:
    std::vector<std::forward_list<std::pair<K,V>>> rootContainer {};
    size_t hash(K key);
    size_t getIndex(size_t hash);
public:
    void insert(K key, V value);
    V get(K key);
    void remove(K key);
};

}

#endif // DSA_STRUCTURES_H
