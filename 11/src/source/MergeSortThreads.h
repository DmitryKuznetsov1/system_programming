#pragma once
#include <mutex>
#include <thread>
#include "MergeSort.h"
#include "my_thread.h"

#define THREAD_MAX std::thread::hardware_concurrency()

std::vector<my_thread> threads(THREAD_MAX);
std::mutex mutex;

template<typename It>
int merge_sort_parallel(It begin, It end);


template<typename It>
size_t add_threads(It first, It last, size_t index = 0) {
    while (index < THREAD_MAX){
        if (!threads[index].joinable()) {
            threads[index] = my_thread([first, last]() { return merge_sort_parallel(first, last); });
            break;
        }
        ++index;
    }
    return index;
}


template<typename It>
int merge_sort_parallel(It begin, It end) {
    size_t i;
    size_t j;

    auto size = std::distance(begin, end);
    if (size < 2)
        return 0;

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
    return 0;
}

long merge_sort_parallel(std::vector<int> &vec) {
    auto start = std::chrono::system_clock::now();
    merge_sort_parallel(vec.begin(), vec.end());
    auto end = std::chrono::system_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    return time.count();
}