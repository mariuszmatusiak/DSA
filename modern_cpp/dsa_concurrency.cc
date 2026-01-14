#include "dsa_concurrency.h"

std::mutex printMutex {};   // global
std::mutex pMutex {};       // producer
std::mutex cMutex {};       // consumer
std::deque<size_t> fifoQueue {}; // a producer-consumer queue
std::atomic_flag ready {};  // global flag for producer and consumer

void threadFunc(const size_t arg, const char * name) {
    for (size_t i = arg; i > 0; --i) {
        {
            std::lock_guard<std::mutex> lockGuard {printMutex}; // RAII, releases when out of scope. To make sure we won't send garbage to stream
            std::cout << std::format("Thread {}, seconds left: {}.", name, i) << std::endl;
        }
        sleep_for(std::chrono::seconds(1));
    }
    std::cout << std::format("Thread {} finished!", name) << std::endl;
}

PrimeNumberPromiseResult getPrimeNumbersAsync(const size_t max, const size_t start) {
    PrimeNumberPromiseResult result {};
    auto t0 = std::chrono::steady_clock::now();
    result.primeNumbers = DSA::Algorithms::Math::getPrimeNumbers(static_cast<ulong>(max), static_cast<ulong>(start));
    result.tdiff = std::chrono::steady_clock::now() - t0;
    result.range = std::make_pair(start, max);
    return result;
}

// This is exactly the same as the one above, but without syntax simplicity of the std::async wrapper
void getPrimeNumbersPromise(const size_t max, const size_t start, std::promise<PrimeNumberPromiseResult> pval) {
    PrimeNumberPromiseResult result {};
    auto t0 = std::chrono::steady_clock::now();
    result.primeNumbers = DSA::Algorithms::Math::getPrimeNumbers(static_cast<ulong>(max), static_cast<ulong>(start));
    result.tdiff = std::chrono::steady_clock::now() - t0;
    result.range = std::make_pair(start, max);
    pval.set_value(result);
}

void producerThread(const size_t arg, const char * name) {
    for (size_t i=0; i < arg; ++i) {
        auto primes = DSA::Algorithms::Math::getPrimeNumbers(static_cast<ulong>(8388608 + i * 10), static_cast<ulong>(0));
        auto newPrime = primes[primes.size()-1];
        std::lock_guard<std::mutex> lockGuard {pMutex};
        std::cout << std::format("Adding {} to queue", newPrime) << std::endl;
        fifoQueue.push_back(newPrime);
    }
    std::lock_guard<std::mutex> lockGuard {pMutex};
    ready.test_and_set(); // mark the queue is ready
}

void consumerThread(const size_t arg, const char * name) {
    while(!ready.test()) { // do the thread until ready flag is set
        std::lock_guard<std::mutex> lockGuard {cMutex}; // what if this is pMutex as well?
        while(!fifoQueue.empty()) { // consume everything at once
            std::cout << std::format("Getting {} from queue", fifoQueue.front()) << std::endl;
            fifoQueue.pop_front();
        }
    }
}
