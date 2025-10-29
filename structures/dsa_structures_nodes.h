#ifndef DSA_STRUCTURES_NODES_H
#define DSA_STRUCTURES_NODES_H

#include "dsa_utils.h"

#include <iostream>
#include <concepts> // for adding constraing and limitations to templates
#include <string>
#include <utility> // for std::move(arg) - tells assignee copy/assignment operator to treats arg as a movable rvalue

using std::shared_ptr;

using DSA::Utils::formatPtr;
using DSA::Utils::log;

namespace DSA::Structures {

template<typename T>
struct Node {
    const T& element;

    // An empty constructor, usage: Node<int> n; Node<int> n{};
    Node() = delete; // also called by the empty initializer list {
    //    log("A no-param default constructor called.");
    // }

    // A parameter default constructor, usage: Node<int> n(5);
    Node(const T& arg) : element{arg} {
        log("Node: a 1-param (const T& arg) ctor called.");
    }

    // A copy constructor, usage: Node<int> n(otherNode);
    // called with copy/assignment operator '='
    Node(const Node& arg) : element{arg.element} { // lvalue reference
        log("Node: a copy (const Node<T>&) ctor called.");
    }

    // A copy assignment operator, usage: n = otherNode;
    Node<T>& operator = (const Node& arg) = delete; // {
    //    if (this != &arg) {
    //        element = arg.element;
    //    }
    //    log("A copy assignment operator= called.");
    //    return *this;
    //}

    // A move constructor, usage: Node<int> n(std::move(otherNode));
    // rvalue reference, primitive types are not movable, noexcept required for move constructor
    Node(Node&& arg) noexcept : element{std::move(arg.element)} {
        log("Node: (Node<T>&&) move ctor called.");
    }

    // An initializer list constructor, usage: Node<int> n{5};
    // doesn't allow narrowing conversion, safer
    Node(const std::initializer_list<T>& l) : element{*l.begin()} {
        log("Node: {init list} ctor called.");
    }

    void printContent() const { std::cout << str() << std::endl; }

    virtual std::string str() const {
        return std::format("Node {:p}: {} at {:p}.",
            formatPtr(*this),
            std::to_string(element),
            formatPtr(element)
        );
    }

    virtual ~Node() {
        log(std::format("Node: node {:p} with element {} deleted.", formatPtr(*this), element));
    }
};

template<typename T>
struct SingleLinkedNode : public Node<T> { // diamond<T> required in inheritence
    using Node<T>::element;
    shared_ptr<SingleLinkedNode> next_right {nullptr};

    SingleLinkedNode() = delete;

    SingleLinkedNode(const T& arg) : Node<T>(arg) { // diamond<T> required as well, Node<T>{} uses init list here
        log("SingleLinkedNode: a 1-param (const T& arg) ctor called.");
    }

    SingleLinkedNode(const SingleLinkedNode& arg) : Node<T>(arg), next_right{arg.next_right} {
        log("SingleLinkedNode: a copy (const SingleLinkedNode<T>&) ctor called.");
    }

    SingleLinkedNode(SingleLinkedNode&& arg) noexcept : Node<T>(arg), next_right{std::move(arg.next_right)} { // rvalue reference, primitive types are not movable, noexcept required for move constructor
        log("SingleLinkedNode: (SingleLinkedNode<T>&&) move ctor called.");
    }

    SingleLinkedNode(const std::initializer_list<T>& l) : Node<T>{l} {
        log("SingleLinkedNode: {initializer list} ctor called.");
    }

    std::string str() const override {
        return std::format("SingleLinkedNode {:p}: {} at {:p} |-R-> {} at {:p}.",
            formatPtr(*this),
            std::to_string(element),
            formatPtr(element),
            (next_right == nullptr) ? "_" : std::to_string(next_right->element),
            formatPtr(*next_right)
        );
    }

    ~SingleLinkedNode() override {
        if (next_right != nullptr) {
            log(std::format("Node {}'s right/next node is not empty.", formatPtr(*this)));
        }
        log(std::format("SingleLinkedNode: node {:p} with element {} deleted.", formatPtr(*this), element));
        // TODO: Clean neighbours here or leave it to containers?
    }
};

template<typename T>
struct DoubleLinkedNode : public SingleLinkedNode<T> {
    using SingleLinkedNode<T>::element; // redundant in non-template derived class declaration, mandatory here
    using SingleLinkedNode<T>::next_right;
    shared_ptr<DoubleLinkedNode> prev_left {nullptr};

    using SingleLinkedNode<T>::SingleLinkedNode; // <- required to make base constructors visible for implicitly compiler-made constructors

    std::string str() const override {
        return std::format("DoubleLinkedNode {:p}: {} at {:p} <-L-| {} at {:p} |-R-> {} at {:p}.",
            formatPtr(*this),
            (prev_left == nullptr) ? "_" : std::to_string(prev_left->element),
            formatPtr(*prev_left),
            std::to_string(element),
            formatPtr(element),
            (next_right == nullptr) ? "_" : std::to_string(next_right->element),
            formatPtr(*next_right)
        );
    }

    ~DoubleLinkedNode() override {
        if (prev_left != nullptr)
            // std::cout << std::format("[{}] left node is not empty.", formatPtr(*this)) << std::endl;
        if (next_right != nullptr)
            // std::cout << std::format("[{}] right node is not empty.", formatPtr(*this)) << std::endl;
       log(std::format("DoubleLinkedNode: node {:p} with element {} deleted.", formatPtr(*this), element));
    }
};

template<typename T>
struct TreeNode : public DoubleLinkedNode<T> {
    using DoubleLinkedNode<T>::element;
    using DoubleLinkedNode<T>::next_right;
    using DoubleLinkedNode<T>::prev_left;
    bool visited {false};

    std::string str() const override {
        return std::format("[{}]: [{}] <-L-| [{}] |-R-> [{}]{}",
            formatPtr(*this),
            (prev_left == nullptr) ? "_" : prev_left->element,
            element,
            (next_right == nullptr) ? "_" : next_right->element,
            visited ? ", visited" : ", not visited"
        );
    }
};

}

#endif // DSA_STRUCTURES_NODES_H
