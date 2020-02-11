#pragma once
#include "MergeSort.h"
#include <thread>
//#include <pthread.h>
#include <mutex>

#define THREAD_MAX std::thread::hardware_concurrency()
#define TIME_ std::chrono::

std::vector<std::thread> threads(THREAD_MAX);
std::mutex mutex;

template<typename It>
void merge_sort_parallel(It begin, It end);


template<typename It>
size_t add_threads(It first, It last, size_t index = 0) {
    while (index < THREAD_MAX){
        if (!threads[index].joinable()) {
            threads[index] = std::thread{merge_sort_parallel<It>, first, last};
            break;
        }
        ++index;
    }
    return index;
}


template<typename It>
void merge_sort_parallel(It begin, It end) {
    size_t i;
    size_t j;

    auto size = std::distance(begin, end);
    if (size < 2)
        return;

    auto mid = std::next(begin, size / 2);

    if (size > 100) {
        std::lock_guard<std::mutex> locked(mutex);
        i = add_threads(begin, mid);
        j = add_threads(mid, end);
    } else {
        i = j = THREAD_MAX;
    }

    if (i == THREAD_MAX)
        merge_sort_parallel(begin, mid);
    else
        threads[i].join();

    if (j == THREAD_MAX)
        merge_sort_parallel(mid, end);
    else
        threads[j].join();

    std::inplace_merge(begin, mid, end);
}

long merge_sort_parallel(std::vector<int> &vec) {
    auto start = std::chrono::system_clock::now();
    merge_sort_parallel(vec.begin(), vec.end());
    auto end = std::chrono::system_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    return time.count();
}
