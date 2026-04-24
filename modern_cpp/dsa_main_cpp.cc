/**
 * A quick reminder of important C++ concepts
 * Copyright (c) 2026 Mariusz Matusiak
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
#include <string>
#include <string_view>  // light-weigth read-only strings
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
#include <utility>      // for std::pair<T1,T2> type, std::cmp_less(_,_)
#include <format>
#include <typeinfo>     // to obtain datatype
#include <algorithm>    // for copy_if, find_if, transform etc.
#include <chrono>       // for std::steady_clock and std::duration
#include <thread>       // for sleep_for, sleep_until, and thread
#include <future>       // for promises
#include <mutex>        // for critical section locks
#include <random>       // for various random number generators
#include <variant>      // for std::variant class
#include <filesystem>   // for std::filesystem
#include <numbers>      // for std::numbers::pi
#include <span>         // for std::span

#define SKIP_INTERRACTION 1
#define UNUSED [[maybe_unused]]  // a C++ standard-compliant attribute to ignore "unused..." warnings

// using namespace std;    // don't put this in a header file, preferably don't put this anywhere
namespace fs = std::filesystem; // alias for std::filesystem

// Global usings
using std::string;
using std::numbers::pi;
using std::this_thread::sleep_for;
using std::this_thread::sleep_until;
using namespace std::chrono_literals;
using namespace DSA;
using DSA::Utils::formatPtr;
using DSA::Structures::Node;

// Global aliases
typedef uint8_t    result_t;    // old-style alias
using   result_u = uint8_t;     // new-style alias
using   ulong    = unsigned long long;

string createDummyString() {
    const string s = "Well...";
    return s;
}

void references(string& s) {
    std::cout << "Regular reference: " << s << ", address: " << &s << std::endl;
}

void references(string&& s) {
    std::cout << "Temporary object reference: " << s << ", address: " << &s << std::endl;
}

class CustomException {
    // not derived from std::exception
};

void demo_InputOutput()
{
    std::cout << "\n=== INPUT / OUTPUT ===" << std::endl;
    std::cout << "Hello world" << std::endl;
    printf("Software version %d.%d\n", DSA_VERSION_MAJOR, DSA_VERSION_MINOR);

    string mystring = "fajnie";
    string mystring2 = "Ale " + mystring;
    std::cout << mystring2 << std::endl;

    // std::cout << "Type sentence (1 word only): ";
    string a;
    // std::cin >> a; // gets only one-word at a time, must be commented if the below is uncommented
    // std::cout << std::format("You typed '{}'.", a) << std::endl;
    // other approach
    std::cout << "Type sentence: ";
    char inputBuffer[256] {};

    #if SKIP_INTERRACTION
    sprintf(inputBuffer, "Sentence %d.", 1);
    #else
    std::cin.getline(inputBuffer, sizeof(inputBuffer));
    #endif
    std::cout << std::format("You typed '{}'.", inputBuffer) << std::endl;
}

void demo_InitializationTechniques()
{
    std::cout << "\n=== MODERN INITIALIZATION TECHNIQUES ===" << std::endl;
    [[maybe_unused]] int a_curly {5}; // list-initialization technique, best since C++11, doesn't allow narrowing conversion, best for primitive types

    [[maybe_unused]] int a_curly_zeroed {}; // empty initializer guaranteed to initialize with zero value

    [[maybe_unused]] int a_old = 5; // copy-initialization almost the same but prone to `implicit narrow conversion`

    [[maybe_unused]] int a_narrowedConv = 5.1; // this will compile

    // [[maybe_unused]] int a_notAllowedNarrowedConv {5.1}; // this won't compile because the parameter is not int.

    [[maybe_unused]] std::vector<int> a_v1 {3, 3}; // two threes (initialization list)
    [[maybe_unused]] std::vector<int> a_v2 (3, 3); // three threes (constructor)
    printContainerInfo(a_v1, true);
    printContainerInfo(a_v2, true);

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
}

void demo_SizeOfs()
{
    std::cout << "\n=== SIZEOFs ===" << std::endl;

    string a = "Ala ma kota";
    std::cout << "Sizeof a: " << sizeof(a) << std::endl;
    std::cout << "Size of a: " << a.size() << std::endl;
    std::cout << "Length of a: " << a.length() << std::endl;
    printf("%lu %lu %lu %lu %lu %lu\n", sizeof(string), sizeof(int), sizeof(char), sizeof(short), sizeof(long), sizeof(long long));
    const char * MyCStyleString = "Ala Ma kota!";
    const char myCStyleStringArray[] = "Ala ma 2 koty!";

    std::cout << MyCStyleString << " has " << sizeof(MyCStyleString) << " bytes, but " << strlen(MyCStyleString) << " characters!" << std::endl;
    std::cout << myCStyleStringArray << " has " << sizeof(myCStyleStringArray) << " bytes, but " << strlen(myCStyleStringArray) << " characters!" << std::endl;
}

void demo_LhsRhsReferences()
{
    std::cout << "\n=== BASIC AND TEMPORARY RHS OBJECT REFERENCES ===" << std::endl;

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
}

void demo_SmartPointers()
{
    std::cout << "\n=== SMART POINTERS ===" << std::endl;

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
}

void demo_STLArrayVector()
{
    std::cout << "\n=== ARRAY / VECTOR ===" << std::endl;

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
}

void demo_STLQueue()
{
    std::cout << "\n=== DOUBLE-ENDED QUEUE ===" << std::endl;

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
}

void demo_STLForwardList()
{
    std::cout << "\n=== FORWARD LIST ===" << std::endl;

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
}

void demo_STLLinkedList()
{
    std::cout << "\n=== DOUBLE-LINKED LIST ===" << std::endl;

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
}

void demo_STLSet()
{
    std::cout << "\n=== SET ===" << std::endl;

    std::set<int> int_set {1, 7, 12};
    int_set.insert(9);
    int_set.erase(20);
    int_set.count(9);
}

void demo_STLMap()
{
    std::cout << "\n=== MAP ===" << std::endl;

    std::map<int,string> int_s_map {{1, "ala"}, {5, "kot"}, {3, "ma"}};
    //int_s_map.insert(
    for (const auto& kv : int_s_map)
        std::cout << kv.first << " -> " << kv.second << std::endl;
}

void demo_ForEach()
{
    std::cout << "\n=== FOREACH ===" << std::endl;

    float vals[] = {3.14, 2.7, -1.0};
    for (float& val : vals)
        std::cout << "Value: " << val << ", address: " << &val << std::endl;
    for (float val : vals)
        std::cout << "Value: " << val << ", address: " << &val << std::endl;
}

void demo_TypeIdWithFormatting()
{
    std::cout << "\n=== TYPEID & FORMATTING ===" << std::endl;

    unsigned long long fact5 = DSA::Algorithms::Math::cfactorial(5U);
    auto oldStyleFact = DSA::Algorithms::Math::factorial(6U);
    std::cout << "Silnia 5: " << fact5 << ", size " << sizeof(fact5) << std::endl;
    std::cout << "Silnia 5 po staremu: " << oldStyleFact << ", size " << sizeof(oldStyleFact) << " type " << typeid(oldStyleFact).name() << std::endl; // this shows implementation-defined name, differs along compilers

    unsigned long long& factRef = fact5;
    // a python style string
    std::cout << std::format("A factorial {}", factRef) << std::endl;
    factRef = oldStyleFact; //reassigning reference value
    std::cout << std::format("A factorial {:_^8}", factRef) << std::endl; //center-aligned for 8 characters with underscores
    std::cout << fact5 << std::endl;

    DSA::OtherUtils::print("Hi {}\n", "me");
}

void demo_AliasesComparison()
{
    std::cout << "\n=== ALIASES COMPARISON ===" << std::endl;

    result_t typedefedResult = 0u;
    result_u usingResult = 0u;
    std::cout << std::format("typedef ({0}) size: {1}, using ({2}) size: {3}", typedefedResult, sizeof(result_t), usingResult, sizeof(result_u)) << std::endl;
}

void demo_ImplicitCasting()
{
    std::cout << "\n=== IMPLICIT CASTING ===" << std::endl;

    bool bool_a = true;
    bool_a = 10;
    std::cout << bool_a << std::endl;
    bool_a = -1;
    std::cout << bool_a << std::endl;
    bool_a = 0;
    std::cout << bool_a << std::endl;
    bool_a = false;
    std::cout << bool_a << std::endl;

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
}

void demo_FileStreamHandling()
{
    std::cout << "\n=== FILE STREAM HANDLING ===" << std::endl;

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
}

void demo_LambdaClosure()
{
    std::cout << "\n=== LAMBDA AND LAMBDA CLOSURE ===" << std::endl;

    // By default treated as const function
    // format:
    // auto x = [/* capture list (=,&,<specific symbol name>) */] (/* parameter list (optional unless other specifiers defined) */) {mutable|constexpr|noexcept} {-> return type (optional)} {/* statements; */}
    // auto x = [/* capture list */](auto p) {return p;};
    std::string greetings { "Hey, hi, hello, "};
    // Closure - a function or lambda which uses parameters outside its lexical scope
    auto myClosureLambdaExpression = [&greetings] (std::string username) {
        std::cout << greetings << username << std::endl;
    };
    myClosureLambdaExpression("Mariusz");
}

void demo_Predicate()
{
    std::cout << "\n=== PREDICATE ===" << std::endl;

    // Predicate - a boolean type lambda
    // Finding all prime numbers in the given vector;
    std::vector<int> v386 {0, 1, 1, 2, 3, 5, 8, 13, 21, 34};
    std::vector<int> v387 {};
    std::vector<int> v388 {};
    auto isPrimeNumberPredicate = [](int i) { return DSA::Algorithms::Math::isPrimeNumber(i); };
    auto isDivBy4 = [](int i) {return i % 4 == 0; };
    std::copy_if(v386.begin(), v386.end(), std::back_inserter(v387), isPrimeNumberPredicate);
    std::copy_if(v386.begin(), v386.end(), std::back_inserter(v388), isDivBy4);
    // std::transform(_, _, _) - to transform vectors/string
    printContainerInfo(v387, true);
    printContainerInfo(v388, true);
}

void demo_FunctionPointers()
{
    std::cout << "\n=== FUNCTION PTRS ===" << std::endl;

    int (*oldCStyleFunPtr)(int arg1, float arg2); // <- can be used as a callback, e.g. in message handlers
    auto newModernCPPStyleFunPtr = std::function<int(int, float)>();
    auto lambdaAdder = [](int arg1, float arg2) -> int {return static_cast<int>(arg1 + arg2);};
    //oldCStyleFunPtr = &lambdaAdder; // assign directly address, won't compile for some reason ?
    oldCStyleFunPtr = lambdaAdder;  // does the same, as function name behaves like a constant function pointer
    newModernCPPStyleFunPtr = lambdaAdder;
    std::cout << std::format("Function pointer to lambda call: {}", oldCStyleFunPtr(5, 2.5)) << std::endl;
    std::cout << std::format("New function pointer to lambda call: {}", newModernCPPStyleFunPtr(6, 2.5)) << std::endl;
}

void demo_RNGs()
{
    std::cout << "\nRANDOM NUMBER GENERATORS ===" << std::endl;

    std::random_device rg1 {};
    std::default_random_engine rg2 {};
    std::minstd_rand0 rg3 {};
    std::minstd_rand rg4{};
    std::mt19937 rg5{};
    std::mt19937_64 rg6{};
    std::ranlux24_base rg7{};
    std::ranlux48_base rg8{};
    std::ranlux24 rg9{};
    std::ranlux48 rg10{};
    std::knuth_b rg11{};
    std::cout << "Random numbers: " <<
        rg1() << ", " <<
        rg2() << ", " <<
        rg3() << ", " <<
        rg4() << ", " <<
        rg5() << ", " <<
        rg6() << ", " <<
        rg7() << ", " <<
        rg8() << ", " <<
        rg9() << ", " <<
        rg10() << ", " <<
        rg11() << ", " << std::endl;
}

void demo_ChronoLibrary()
{
    std::cout << "\n=== CHRONO LIBRARY ===" << std::endl;

    using std::chrono::steady_clock;
    using std::chrono::duration;
    using seconds = duration<double>;
    using milliseconds = duration<double, std::milli>;
    using microseconds = duration<double, std::micro>;
    using fps24 = duration<unsigned long, std::ratio<1, 24>>;

    auto currentTime = std::chrono::system_clock::now();
    printf("Current system clock is {:%F %T %Z}\n", currentTime);
    std::cout << currentTime.time_since_epoch() << std::endl;

    //getExecutionTime
}

void demo_FormatLibrary()
{
    std::cout << "\n=== OUTPUT FORMATTING, FORMAT LIBRARY ===" << std::endl;

    const char *             cString {"Hello"};
    const std::string_view cppString {"World"};
    std::cout << std::format("{} {}",   cString, cppString) << std::endl;
    std::cout << std::format("{1} {0}", cString, cppString) << std::endl;

    const double oneTenth {1.1};
    const double dPi {pi};
    std::cout << std::format("val1: {:.5} val2: {:.5}",   oneTenth, dPi) << std::endl;
    std::cout << std::format("val1: {1:.7} val2: {0:.7}", oneTenth, dPi) << std::endl;

    const uint64_t variable {12u};
    const uint64_t variable2 {123456789u};
    std::cout << "Left-aligned 8 characters with *-padding\n"
                << std::format("[{:*<8}]", variable) << std::endl;

    std::cout << "Right-aligned 8 characters with 0-padding\n"
                << std::format("[{:0>8}]", variable) << std::endl;

    std::cout << "Center-aligned 8 characters with -padding\n"
                << std::format("[{:^8}]", variable) << std::endl;

    std::cout << "Center-aligned 8 characters with _-padding\n"
                << std::format("[{:_^8}]", variable) << std::endl;

    std::cout << "Center-aligned 8 characters with _-padding\n"
                << std::format("[{:_^8}]", variable2) << std::endl; // expanded to 9 characters

    const Fraction<int>    f1 {2, 5};
    const Fraction<int>    f2 {5};
    const Fraction<double> f3 {2.5, 3.7};
    std::cout << "Fraction 1: " << std::format("{}", f1) << std::endl; // calling custom formatter
    std::cout << "Fraction 2: " << std::format("{}", f2) << std::endl;
    std::cout << "Fraction 3: " << std::format("{}", f3) << std::endl;
}

void demo_Sleeps()
{
    std::cout << "\n=== SLEEPS ===" << std::endl;
    std::cout << "Let's wait a bit, e.g. 1.5s..." << std::endl; //endl is required for flushing before sleeping, otherwise it won't be printed
    auto t0 = std::chrono::steady_clock::now(); // returns a current time point using static function now()
    sleep_for(1s + 500ms);
    std::cout << "Now 2 more seconds..." << std::endl;
    sleep_until(std::chrono::steady_clock::now() + 2s);
    std::chrono::duration<double> tdiff = std::chrono::steady_clock::now() - t0;
    std::cout << "Thanks for waiting " << tdiff << std::endl;
}

void demo_Threads_detach()
{
    std::cout << "\n=== THREADS - DETACH (CONT. OWNER THREAD) ===" << std::endl;
    std::thread T1(threadFunc, 1, "T1");
    std::thread T2(threadFunc, 2, "T2");
    std::thread T3(threadFunc, 3, "T3");
    T1.detach(); // start the threads but continue executing main
    T2.detach();
    T3.detach();

    std::cout << "Main thread is still working, let's wait some time for other threads before completing main()" << std::endl;
    sleep_for(5s);
}

void demo_Threads_join()
{
    std::cout << "\n=== THREADS - JOIN (PAUSE OWNER THREAD) ===" << std::endl;
    std::cout << "Now run these threads again but in join() mode..." << std::endl;
    std::thread T1b(threadFunc, 1, "T1"); // we need to create another thread objects that will do the work
    std::thread T2b(threadFunc, 3, "T2");
    std::thread T3b(threadFunc, 5, "T3");

    // without explicit join() on all threads main works like join() is called, e.g. wait for threads ending. But libc++api: terminating zsh:abort occurs
    T3b.join(); // block main until all complete; wait() to be used with std::async
    T2b.join(); // since we waited for longer T3b this might be redundant already
    T1b.join(); // since we waited for longer T3b this might be redundant already

    std::cout << "Main thread waited for all other threads. Now can close..." << std::endl;
}

void demo_Threads_Async()
{
    std::cout << "\n=== ASYNC - THREAD RETURNING A VALUE ===" << std::endl;
    constexpr size_t numOfThreads {10};
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
}

void demo_Threads_FuturePromises()
{
    std::cout << "\n=== PROMISES, FUTURE  ===" << std::endl;
    constexpr size_t numOfThreads {10};
    size_t maxRange {0x800u};
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
}

void demo_Threads_ProducerConsumer()
{
    std::cout << "\n=== PRODUCER / CONSUMER ===" << std::endl;
    std::thread tp {producerThread, 2, "Producer"};
    std::thread tc {consumerThread, 0, "Consumer"};

    tp.detach();
    tc.detach();
}

void demo_OptionalClass()
{
    std::cout << "\n=== OPTIONAL CLASS ===" << std::endl;
    auto signedFactorialPos5 = DSA::Algorithms::Math::sfactorial(5);
    auto signedFactorialZero = DSA::Algorithms::Math::sfactorial(0);
    auto signedFactorialNeg5 = DSA::Algorithms::Math::sfactorial(-5);
    if (signedFactorialPos5.has_value())
        std::cout << "Optional factorial of +5 is: " << signedFactorialPos5.value() << std::endl;
    if (signedFactorialZero.has_value())
        std::cout << "Optional factorial of 0 is: " << signedFactorialZero.value() << std::endl;
    if (signedFactorialNeg5.has_value())
        std::cout << "Optional factorial of -5 is: " << signedFactorialPos5.value() << std::endl;
    else
        std::cout << "Optional factorial of -5 not exists." << std::endl;
}

void demo_AnyClass(void)
{
    std::cout << "\n=== ANY CLASS ===" << std::endl;
    DSA::Utils::printObject(5u);
    DSA::Utils::printObject(-5);
    DSA::Utils::printObject(std::string{"Bonjour"});
    DSA::Utils::printObject("Bonjour");
    DSA::Utils::printObject(std::vector{1, 2, 3});
}

void demo_VariantClass(void)
{
    std::cout << "\n=== VARIANT CLASS ===" << std::endl;
    using v_Example = std::variant<ExampleTwo, ExampleThree>; // type definition tuple with indexes 0, 1
    std::vector<v_Example> examples {ExampleTwo(), ExampleThree()};
    // Find specific class by iterating using indexes
    for (const auto& element : examples) {
        auto index = element.index();
        if (index == 0) get<ExampleTwo>(element).printHi();
        if (index == 1) get<ExampleThree>(element).printHi();
    }
    // Find specific class by iterating using get_if->ptr with if assignment
    for (const auto& element : examples) {
        if (const auto& o = get_if<ExampleTwo>(&element); o) o->printHi();
        if (const auto& o = get_if<ExampleThree>(&element); o) o->printHi();
    }
    // Just execute printHi() using functor structure and std::visit
    for (const auto& element : examples) {
        std::visit(ExamplesHi{}, element);
    }
}

void demo_StructuredBindings()
{
    std::cout << "\n=== STRUCTURED BINDINGS ===" << std::endl;
    std::tuple<int, float, std::string> myRecord {5, 7.5, std::string{"Ala"}};
    const auto [x1, x2, x3] = myRecord; // also works with structs, pairs, C-strings, C-arrays, etc and with reference operator.
    std::cout << "{" << x1 << ", " << x2 << ", " << x3 << "}" << std::endl;
}

void demo_FileSystemLibrary()
{
    std::cout << "\n=== FILESYSTEM LIBRARY ===" << std::endl;
    constexpr const char* filePath {"file.txt"};
    constexpr const char* homeDir {"/Users/mariusz/Projects/Trainings/DSA/output"};

    fs::path p {filePath};
    std::cout << p << std::endl;
    std::cout << fs::absolute(p) << std::endl;

    if (fs::exists(homeDir)) {
        std::cout << "Dir " << fs::absolute(homeDir) << " exists!" << std::endl;
    }

    try {
        std::cout << std::format("pwd: {}", fs::current_path().c_str()) << std::endl;
        std::cout << "cd to homeDir" << std::endl;
        fs::current_path(homeDir);
        std::cout << std::format("pwd: {}", fs::current_path().c_str()) << std::endl;

        std::cout << (fs::path{homeDir} += filePath) << std::endl; // simple concat
        std::cout << (fs::path{homeDir} /= filePath) << std::endl; // append with /
        std::cout << fs::canonical(fs::path(".")) << std::endl;
        std::cout << fs::canonical(fs::path("x.")) << std::endl;

    } catch (const fs::filesystem_error& e) {
        std::cout << e.what() << std::endl;
    }
}

void demo_SpaceshipOperator()
{
    std::cout << "\n=== SPACESHIP OPERATOR ===" << std::endl;
    constexpr Fraction<int> f1 {1, 2};
    constexpr Fraction<int> f2 {7, 16};
    // The below lines will work unless operator== and operator<-> are overloaded
    // static_assert(f2 > f1);
    // static_assert(f2 >= f1);
    // static_assert(f1 < f2);
    // static_assert(f1 <= f2);
    static_assert(f1 > f2);
    static_assert(f1 >= f2);
    static_assert(f2 < f1);
    static_assert(f2 <= f1);
    static_assert(f1 != f2);
    // static_assert(f1 == f2);
    if (f2 > f1)
        std::cout << std::format("{} is greater than {}", f2, f1) << std::endl;
    else
        std::cout << std::format("{} is greater than {}", f1, f2) << std::endl;
}

void demo_unSignedIntegerComparisons()
{
    std::cout << "\n=== (UN)SIGNED INTEGER COMPARISONS ===" << std::endl;
    const int x {-10};
    const unsigned int y {10};
    static_assert(x > y); // because of implicit casting and 2-compliment representation
    static_assert(std::cmp_less(x, y)); // from <utility>
    static_assert(std::cmp_less_equal(x, y));
    static_assert(std::cmp_greater(y, x));
    static_assert(std::cmp_greater_equal(y, x));
    static_assert(std::cmp_not_equal(x, y));
    static_assert(!(std::cmp_equal(x, y)));
}

void demo_SpanClass()
{
    std::cout << "\n=== SPAN CLASS ===" << std::endl;
    char cArray[] {'a', 'l', 'a'};
    std::vector<int> cppVec {1, 2, 3};
    std::array<double, 3> cppArr {-1.5, -0.5, 3.3};

    auto spannedCArray = toSpanView<char>(cArray);
    auto spannedCppVec = toSpanView<int>(cppVec);
    auto spannedCppArr = toSpanView<double>(cppArr);

    std::cout << std::format("Spanned char array length {}, size {} bytes, elements: ", spannedCArray.size(), spannedCArray.size_bytes()) << std::endl;
    for (const auto& item : spannedCArray) std::cout << item << ", ";
    std::cout << std::endl;

    std::cout << std::format("Spanned int vector length {}, size {} bytes, elements: ", spannedCppVec.size(), spannedCppVec.size_bytes()) << std::endl;
    for (const auto& item : spannedCppVec) std::cout << item << ", ";
    std::cout << std::endl;

    std::cout << std::format("Spanned double std::array length {}, size {} bytes, elements: ", spannedCppArr.size(), spannedCppArr.size_bytes()) << std::endl;
    for (const auto& item : spannedCppArr) std::cout << item << ", ";
    std::cout << std::endl;
}

int main (void)
{
    // === INPUT / OUTPUT ===
    demo_InputOutput();

    // === MODERN INITIALIZATION TECHNIQUES ===
    demo_InitializationTechniques();

    // === ARCHITECTURE SIZEOFS ===
    demo_SizeOfs();

    // === BASIC AND TEMPORARY RHS OBJECT REFERENCES ===
    demo_LhsRhsReferences();

    // === SMART POINTERS ===
    demo_SmartPointers();

    // === SEQUENTIAL DATA STRUCTURES ===

    //  === ARRAY / VECTOR ===
    demo_STLArrayVector();

    //  === DOUBLE-ENDED QUEUE ===
    demo_STLQueue();

    // === FORWARD LIST ===
    demo_STLForwardList();

    // === DOUBLE-LINKED LIST ===
    demo_STLLinkedList();

    // === SET ===
    demo_STLSet();

    // === MAP ===
    demo_STLMap();

    // === FOREACH ===
    demo_ForEach();

    // === TYPEID & FORMATTING ===
    demo_TypeIdWithFormatting();

    // === ALIASES COMPARISON ===
    demo_AliasesComparison();

    // === OUTPUT FORMATTING, FORMAT LIBRARY ===
    demo_FormatLibrary();

    // === IMPLICIT CASTING ===
    demo_ImplicitCasting();

    // === FILE STREAM HANDLING ===
    demo_FileStreamHandling();

    // === LAMBDA AND LAMBDA CLOSURE ===
    demo_LambdaClosure();

    // === PREDICATE ===
    demo_Predicate();

    // === FUNCTION PTRS ===
    demo_FunctionPointers();

    // === SLEEPS ===
    //demo_Sleeps();

    // === THREADS - DETACH (CONT. OWNER THREAD) ===
    //demo_Threads_detach();

    // === THREADS - JOIN (PAUSE OWNER THREAD) ===
    //demo_Threads_join();

    // === ASYNC - THREAD RETURNING A VALUE ===
    //demo_Threads_Async();

    // === PROMISES, FUTURE  === - original way without the async wrapper
    //demo_Threads_FuturePromises();

    // === PRODUCER / CONSUMER ===
    //demo_Threads_ProducerConsumer();

    // === RANDOM NUMBER GENERATORS ===
    demo_RNGs();

    // === CHRONO LIBRARY ===
    demo_ChronoLibrary();

    // === OPTIONAL CLASS ===
    demo_OptionalClass();

    // === ANY CLASS ===
    demo_AnyClass();

    // === VARIANT CLASS ===
    demo_VariantClass();

    // === STRUCTURED BINDINGS ===
    demo_StructuredBindings();

    // === FILESYSTEM LIBRARY ===
    demo_FileSystemLibrary();

    // === SPACESHIP OPERATOR ===
    demo_SpaceshipOperator();

    // === (UN)SIGNED INTEGER COMPARISONS ===
    demo_unSignedIntegerComparisons();

    // === SPAN CLASS ===
    demo_SpanClass();
}
