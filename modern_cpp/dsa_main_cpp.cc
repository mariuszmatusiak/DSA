/**
 * A quick reminder of important C++ concepts
 * Copyright (c) 2025 Mariusz Matusiak
 */

#include "dsa_classes.h"
#include "dsa_config.h"
#include "dsa_structures.h"
#include "dsa_algorithms.h"
#include "dsa_utils.h"
#include "dsa_concurrency.h"

#include <iostream>
#include <fstream>      // for files
#include <cstdlib>
#include <cstring>      // to handle C-style strings
#include <exception>
#include <stdexcept>
#include <vector>
#include <set>
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <iterator>
#include <set>
#include <map>
#include <tuple>
#include <utility>      // for std::pair<T1,T2> type
#include <format>
#include <typeinfo>     // to obtain datatype
#include <algorithm>    // for copy_if, find_if, transform etc.
#include <chrono>       // for steady_clock and duration
#include <thread>       // for sleep_for and sleep_until
#include <future>       // for promises
#include <mutex>        // for locks

using namespace std;    // don't put this in a header file, preferably don't put this anywhere
using namespace DSA;

using ::chrono::steady_clock;
using ::chrono::duration;
using ::this_thread::sleep_for;
using ::this_thread::sleep_until;
using namespace ::chrono_literals;

using DSA::Utils::formatPtr;
using DSA::Structures::Node;

// aliases
typedef uint8_t result_t;
using result_u = uint8_t;
using ulong = unsigned long long;

string createDummyString() {
    const string s = "Well...";
    return s;
}

void references(string& s) {
    cout << "Regular reference: " << s << ", address: " << &s << endl;
}

void references(string&& s) {
    cout << "Temporary object reference: " << s << ", address: " << &s << endl;
}

class CustomException {
    // not derived from std::exception
};

int main (void)
{
    cout << "Hello world" << endl;
    printf("Software version %d.%d\n", DSA_VERSION_MAJOR, DSA_VERSION_MINOR);

    string mystring = "fajnie";
    string mystring2 = "Ale " + mystring;
    cout << mystring2 << endl;

    // cout << "Type sentence (1 word only): ";
    string a;
    // cin >> a; // gets only one-word at a time, must be commented if the below is uncommented
    // cout << std::format("You typed '{}'.", a) << endl;
    // other approach
    cout << "Type sentence: ";
    char inputBuffer[256] {};
    cin.getline(inputBuffer, sizeof(inputBuffer));
    cout << std::format("You typed '{}'.", inputBuffer) << endl;

    // === ARCHITECTURE SIZEOFS ===

    cout << "Sizeof a: " << sizeof(a) << endl;
    cout << "Size of a: " << a.size() << endl;
    cout << "Length of a: " << a.length() << endl;
    printf("%lu %lu %lu %lu %lu %lu\n", sizeof(string), sizeof(int), sizeof(char), sizeof(short), sizeof(long), sizeof(long long));
    const char * MyCStyleString = "Ala Ma kota!";
    const char myCStyleStringArray[] = "Ala ma 2 koty!";

    cout << MyCStyleString << " has " << sizeof(MyCStyleString) << " bytes, but " << strlen(MyCStyleString) << " characters!" << endl;
    cout << myCStyleStringArray << " has " << sizeof(myCStyleStringArray) << " bytes, but " << strlen(myCStyleStringArray) << " characters!" << endl;

    // === BASIC AND TEMPORARY OBJECT REFERENCES ===

    // & - reference
    // && - reference to temporary object

    string s = "Oh well then...";
    references(createDummyString());
    references(s);
    string s2 = "Hi!... " + s;
    std::cout << s2 << std::endl;

    // Additional methods:
    // s2.insert(it, what)
    // s2.erase(it)
    // s2.replace(pos, count, "new content");
    // s2.substr(pos, letterCount);
    // s2.find("as")->positionNumber
    // s2.rfind() - same as above but backwards

    ExampleOne ex;
    ex.printHi();
    const ExampleOne& ref = ex;
    ref.printHi();
    //ref.printWOConst();
    ExampleOne& nonConstRef = ex;
    nonConstRef.printWOConst();
    nonConstRef.printState();

    std::cout << "Size comparison: object instance " << sizeof(ex) << ", const reference " << sizeof(ref) << ", non-const reference " << sizeof(nonConstRef) << ", pointer " << sizeof(&ex) << ", class " << sizeof(ExampleOne) << std::endl;

    ExampleTwo ex2;
    ex2.printHi();
    ExampleOne * examplePtr = &ex2;
    examplePtr->printHi();

    // === OPERATOR+ OVERLOADING ===
    ExampleOne ex3 = ex + ex2;
    std::cout << "ex3 assigned object address: " << &ex3 << std::endl;

    ex.printState();
    ex2.printState();
    ex3.printState();
    (ex3 + ex2);

    ex3 += ex3;
    ex3.printState();

    try {
        ex3.throwException();
    } catch (const std::exception& ex_ref) {
        std::cout << "Exception occured: " << ex_ref.what() << std::endl;
    } catch (...) { // catches ANY exception
        std::cout << "Other exception to be rethrown!" << std::endl;
        throw;
    }

    try {
        throw CustomException();
    } catch (const std::exception& ex_ref) {
        std::cout << "Exception occured: " << ex_ref.what() << std::endl;
    } catch (...) { // catches ANY exception
        std::cout << "Other unknown exception to be rethrown!" << std::endl;
    }

    //  === SMART POINTERS ===

    // use shared_ptr/unique_ptr as often as possible, is using new (heap) initialize stuff with zeros always
    std::shared_ptr<ExampleOne> ptr1(new ExampleOne()); // to hold multiple references to the same object, deallocates when all references are gone
    std::unique_ptr<ExampleOne> ptr2(new ExampleTwo()); // to hold one reference to the object <auto> not allowed in template argument
    std::weak_ptr<ExampleOne>   ptr3 = ptr1; // to access underlying object of shared_ptr without causing object to stay allocated, used to prevent circular referencing
    // std::weak_ptr<ExampleOne>   ptr4(new ExampleOne()); // this won't compile
    // std::weak_ptr<ExampleOne>   ptr4 = ptr2; // this won't compile either
    auto * ptr5 = new ExampleTwo();
    ptr1->printState();
    ptr2->printState();
    {
        std::weak_ptr<ExampleOne>   ptr4 = ptr1; // this is fine
        std::cout << "ptr1 pre-lock usage count: " << ptr1.use_count() << std::endl;
        auto ptr4_1 = ptr4.lock(); // same
        ptr4_1->printState();
        std::cout << "ptr1 post-lock usage count: " << ptr1.use_count() << std::endl;
    }
    // ptr3->printState(); // these don't compile
    // ptr4->printState();
    auto ptr3_1 = ptr3.lock(); // convert weak ptr to shared in order to reference the object;
    ptr3_1->printState(); // but this do
    ptr5->printState();
    delete ptr5;
    std::cout << "ptr1 usage count: " << ptr1.use_count() << std::endl;

    // === SEQUENTIAL DATA STRUCTURES ===
    // === ARRAY / VECTOR ===
    std::array<int,3> num_array = {0, 1, 2}; // fixed-size, 3-elements-long array
    std::vector<int> num_vector = {0, 1, 2}; // resizeable container
    int cStyleArray[] = {-3, -2, -1, 0, 1, 2, 3};
    std::vector<int> vector_from_array(cStyleArray, cStyleArray + sizeof(cStyleArray)/sizeof(int)); //copy c-tor
    printContainer(vector_from_array);

    // === Data Accessors ===

    printf("%d %d %d %d 0x%lX\n",
        num_array.at(1),
        num_array[1],
        num_array.front(),
        num_array.back(),
        reinterpret_cast<std::uintptr_t>(num_array.data()));

    // === Forward Iterators ===
    for (auto it = num_array.begin(); it != num_array.end(); it++)
        std::cout << it << ": " << *it << std::endl;

    // === Backward Iterators ===
    for (auto it = num_array.rbegin(); it != num_array.rend(); it++)
        std::cout << /* it << ": " << */ *it << std::endl; // suprisingly printing it doesnt work here

    // === Checking Capacity ===
    std::cout << "Is empty: " << num_array.empty() << ", size: " << num_array.size() << ", max size: " << num_array.max_size() << std::endl;

    // === Filling the entire content ===
    num_array.fill(5);
    for (auto& element : num_array)
        std::cout << &element << ": " << element << std::endl;

    // === DOUBLE-ENDED QUEUE ===
    std::deque<int> num_deque{1, 2, 3};
    num_deque.push_back(5);
    num_deque.push_front(0);

    auto num_deque_it = num_deque.begin();
    ++num_deque_it;
    num_deque_it = num_deque.insert(num_deque_it+1, 3, 10); // insert three 10s at second position
    printf("Iterator 0x%p\n", formatPtr(num_deque_it));
    printf("Iterator 0x%p\n", formatPtr(*num_deque_it));
    printContainer(num_deque);

    num_deque_it = num_deque.erase(num_deque_it);
    printContainer(num_deque);

    num_deque.resize(num_deque.size()+3u, 100); // resize with 3 extra elements.
    printContainer(num_deque);
    printContainerInfo(num_deque);

    num_deque.clear();
    printContainer(num_deque);
    printContainerInfo(num_deque);

    // === FORWARD LIST ===
    std::forward_list<string> list1 = {"Ala", "Ma", "Kota"};
    std::forward_list<string> list2 = {"Pies", "Ma", "Alę"};
    std::forward_list<string> list3 = {list1};
    std::cout << "List1: " << std::endl;
    printContainer(list1);
    std::cout << "List2: " << std::endl;
    printContainer(list2);
    std::cout << "List3: " << std::endl;
    printContainer(list3);
    list2.sort();
    list3.sort();
    std::cout << "Not-sorted List1: " << std::endl;
    printContainer(list1);
    std::cout << "Sorted List2: " << std::endl;
    printContainer(list2);
    std::cout << "Sorted List3: " << std::endl;
    printContainer(list3);
    list3.merge(list2);
    std::cout << "Not-Sorted List1: " << std::endl;
    printContainer(list1);
    std::cout << "Merged Sorted List2: " << std::endl;
    printContainer(list2);
    std::cout << "Merged Sorted List3: " << std::endl;
    printContainer(list3);

    // === DOUBLE-LINKED LIST ===
    std::list<int> ints {0, 1, 4, 5, 6, 122, 4, 2, 5, 88, 4, 2, 7};
    std::list<int> tens {0, 10, 20, 50, 30};
    printContainerInfo(ints);
    auto ints_it = ints.begin();
    ++ints_it;
    ++ints_it;
    ints.splice(ints_it, tens);
    printContainerInfo(ints);
    printContainerInfo(tens);
    ints.reverse();
    printContainerInfo(ints);
    ints.unique(); // removes only consecutive occurences
    printContainerInfo(ints);
    ints.sort();
    ints.unique(); //check after sorting
    printContainerInfo(ints);
    ints.remove_if([](int n) { // remove all elements smaller than 7
        return n < 7;
    });
    printContainerInfo(ints);

    // === SET ===
    std::set<int> int_set {1, 7, 12};
    int_set.insert(9);
    int_set.erase(20);
    int_set.count(9);

    // === MAP ===
    std::map<int,string> int_s_map {{1, "ala"}, {5, "kot"}, {3, "ma"}};
    //int_s_map.insert(
    for (const auto& kv : int_s_map)
        std::cout << kv.first << " -> " << kv.second << std::endl;

    // C-style array with foreach
    float vals[] = {3.14, 2.7, -1.0};
    for (float& val : vals)
        cout << "Value: " << val << ", address: " << &val << endl;
    for (float val : vals)
        cout << "Value: " << val << ", address: " << &val << endl;

    // === TYPEID ===
    unsigned long long fact5 = ::Algorithms::Math::cfactorial(5U);
    auto oldStyleFact = ::Algorithms::Math::factorial(6U);
    cout << "Silnia 5: " << fact5 << ", size " << sizeof(fact5) << endl;
    cout << "Silnia 5 po staremu: " << oldStyleFact << ", size " << sizeof(oldStyleFact) << " type " << typeid(oldStyleFact).name() << endl; // this shows implementation-defined name, differs along compilers

    unsigned long long& factRef = fact5;
    // a python style string
    cout << std::format("A factorial {}", factRef) << endl;
    factRef = oldStyleFact; //reassigning reference value
    cout << std::format("A factorial {:_^8}", factRef) << endl; //center-aligned for 8 characters with underscores

    // === OLD-STYLE AND NEW-STYLE INITIALIZATION ===
    UnitializedStruct struct1;
    UnitializedStruct struct2 {};
    InitializedStruct struct3;
    InitializedStruct struct4 {};
    InitializedStruct struct5 {'v', -5, 10, 10000000000ULL};
    struct1.print(); //this prints mess
    struct2.print(); //this prints defaults (zeros)
    struct3.print(); //this prints defaults (zeros)
    struct4.print(); //this prints defaults (zeros)
    struct5.print();

    // === ALIASES COMPARISON ===
    result_t typedefedResult = 0u;
    result_u usingResult = 0u;
    std::cout << std::format("typedef ({0}) size: {1}, using ({2}) size: {3}", typedefedResult, sizeof(result_t), usingResult, sizeof(result_u)) << std::endl;

    // === OUTPUT FORMATTING ===
    uint64_t formattedVariable {12u};
    std::cout << std::format("variable: {0}, \nleft-aligned 5 chars with *-padding: \n{1:*<5}, \nright-aligned 4 characters with 0-padding: \n{2:0>4}",
        formattedVariable, formattedVariable, formattedVariable) << std::endl;

    // === IMPLICIT CASTING ===
    bool bool_a = true;
    bool_a = 10;
    cout << bool_a << endl;
    bool_a = -1;
    cout << bool_a << endl;
    bool_a = 0;
    cout << bool_a << endl;
    bool_a = false;
    cout << bool_a << endl;

    // Node<string> myStringNode1; // won't compile - call to deleted constructor
    // Node<string> myStringNode2 {}; // the same here
    // Node<string> myStringNode3 (); // this is interpreted as a function declaration not instantiation
    // Node<string> myStringNode3("Kot"); // But this one works okay
    // Node<string> myStringNode4 = "Ma"s; // use one param constructor but with s suffix only (non C-style string)
    // Node<string> myStringNode5 {"Ala"};
    // Node myStringNode6 {"koty"s}; // type deduction done by the compiler TODO - to be fixed
    // Node<string> myStringNode6 {"Ala", nullptr, nullptr}; // but this fails also as no matching constructor exists
    // myStringNode1.print();
    // myStringNode2.print();
    // myStringNode3.print();
    // myStringNode4.print();
    // myStringNode5.print();
    // myStringNode6.print();

    printAll(bool_a, fact5, a);

    // === FILE STREAM HANDLING ===
    static const char * cStyleFilename {"./logs.txt"};
    std::ofstream outputFileStream(cStyleFilename);
    outputFileStream << "<timestamp1>: " << " log1\n";
    outputFileStream << "<timestamp2>: " << " log2\n";
    outputFileStream << "<timestamp3>: " << " log3\n";
    outputFileStream.close();

    char fileLineBuffer[256] {};
    std::ifstream fin(cStyleFilename);
    while(fin.good()) {
        fin.getline(fileLineBuffer, sizeof(fileLineBuffer));
        std::cout << fileLineBuffer << std::endl;
    }
    fin.close();

    DSA::OtherUtils::print("Hi {}\n", "me");

    // === LAMBDA CLOSURE ===
    std::string greetings { "Hey, hi, hello, "};
    auto myClosureLambdaExpression = [&greetings] (std::string username) {
        std::cout << greetings << username << std::endl;
    };
    myClosureLambdaExpression("Mariusz");

    // === PREDICATE ===
    // Finding all prime numbers in the given vector;
    std::vector<int> v386 {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 100};
    std::vector<int> v387 {};
    auto isPrimeNumberPredicate = [](int i) { return DSA::Algorithms::Math::isPrimeNumber(i); };
    std::copy_if(v386.begin(), v386.end(), std::back_inserter(v387), isPrimeNumberPredicate);
    printContainerInfo(v387);

    // === SLEEPS ===
    std::cout << "Let's wait a bit, e.g. 3.5s..." << std::endl; //endl is required for flushing before sleeping, otherwise it won't be printed
    auto t0 = std::chrono::steady_clock::now(); // returns a current time point using static function now()
    sleep_for(3s + 500ms);
    std::cout << "Now 2 more seconds..." << std::endl;
    sleep_until(std::chrono::steady_clock::now() + 2s);
    std::chrono::duration<double> tdiff = std::chrono::steady_clock::now() - t0;
    std::cout << "Thanks for waiting " << tdiff << std::endl;

    // === THREADS - DETACH ===
    thread T1(threadFunc, 10, "T1");
    thread T2(threadFunc, 15, "T2");
    thread T3(threadFunc, 20, "T3");
    T1.detach(); // start the threads but continue executing main
    T2.detach();
    T3.detach();

    std::cout << "Main thread is still working, let's wait some time for other threads before completing main()" << std::endl;
    sleep_for(21s);

    // === THREADS - JOIN ===
    std::cout << "Now run these threads again but in join() mode..." << std::endl;
    thread T1b(threadFunc, 10, "T1"); // we need to create another thread objects that will do the work
    thread T2b(threadFunc, 15, "T2");
    thread T3b(threadFunc, 20, "T3");

    // without explicit join() on all threads main works like join() is called, e.g. wait for threads ending. But libc++api: terminating zsh:abort occurs
    T3b.join(); // block main until all complete; wait() to be used with std::async
    T2b.join(); // since we waited for longer T3b this might be redundant already
    T1b.join(); // since we waited for longer T3b this might be redundant already

    std::cout << "Main thread waited for all other threads. Now can close..." << std::endl;

    // === ASYNC ===
    constexpr size_t numOfThreads {16};
    size_t maxRange {0x800u};
    std::list<std::future<PrimeNumberPromiseResult>> futureList; // or listOfFuturePromises
    for (int i = 0; i < numOfThreads; ++i) {
        // appends a list by calling a matching object constructor internally passing given parameters to it,
        // skips redundant copy & move operations normally done in push_back()
        futureList.emplace_back(std::async(getPrimeNumbersAsync, maxRange, 0u));
        maxRange <<= 1; // 0x800u (2048) * 2^{15} maximum = 0x4000000u (~67M)
    }
    for (auto& futureObj : futureList) {
        auto [tdiff, range, primeNumbers] = futureObj.get(); // block and wait for the promise and assign using structured binding from C++17
        std::cout << std::format("Found {} prime numbers in [{},{}] in {} seconds.", primeNumbers.size(), range.first, range.second, tdiff) << std::endl;
    }

    // === PROMISES, FUTURE  === - original way without the async wrapper
    maxRange = 0x800u;
    std::list<std::future<PrimeNumberPromiseResult>> futureList2;
    for (int i = 0; i < numOfThreads; ++i) {
        std::promise<PrimeNumberPromiseResult> promiseObj {};
        std::future<PrimeNumberPromiseResult> futureObj = promiseObj.get_future();
        futureList2.emplace_back(std::move(futureObj));
        std::thread primeThread(getPrimeNumbersPromise, maxRange, 0u, std::move(promiseObj));
        primeThread.detach(); // run in the background
        maxRange <<= 1;
    }
    for (auto& futureObj : futureList2) {
        auto [tdiff, range, primeNumbers] = futureObj.get();
        std::cout << std::format("Found {} prime numbers in [{},{}] in {} seconds.", primeNumbers.size(), range.first, range.second, tdiff) << std::endl;
    }

    // === PRODUCER / CONSUMER ===
    std::thread tp {producerThread, 10, "Producer"};
    std::thread tc {consumerThread, 0, "Consumer"};

    tp.join();
    tc.join();
}
