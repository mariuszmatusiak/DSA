#ifndef DSA_CONCURRENCY_H
#define DSA_CONCURRENCY_H

#include "dsa_algorithms.h"

#include <chrono>       // for ::chrono::steady_clock and ::chrono::duration
#include <thread>       // for ::this_thread::sleep_for and ::this_thread::sleep_until
#include <future>       // for promises
#include <mutex>        // for locks
#include <iostream>

using std::chrono::steady_clock;
using std::chrono::duration;
using std::this_thread::sleep_for;
using std::this_thread::sleep_until;
using namespace std::chrono_literals;
using ulong = unsigned long long;

struct PrimeNumberPromiseResult {
    duration<double> tdiff;
    std::pair<ulong, ulong>  range;
    std::vector<ulong> primeNumbers;
};

PrimeNumberPromiseResult getPrimeNumbersAsync(const size_t max, const size_t start);

void getPrimeNumbersPromise(const size_t max, const size_t start, std::promise<PrimeNumberPromiseResult> pval);

void threadFunc(const size_t arg, const char * name);

void producerThread(const size_t arg, const char * name);

void consumerThread(const size_t arg, const char * name);

#endif // DSA_CONCURRENCY_H
