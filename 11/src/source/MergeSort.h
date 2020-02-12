#pragma once
#include <algorithm>
#include <chrono>
#include <vector>


template<typename It>
void merge_sort(It begin, It end)
{
    auto size = std::distance(begin, end);
    if (size < 2)
        return;

    auto mid = std::next(begin, size / 2);
    merge_sort(begin, mid);
    merge_sort(mid, end);
    std::inplace_merge(begin, mid, end);
}


long merge_sort(std::vector<int> &vec) {
    auto start = std::chrono::system_clock::now();
    merge_sort(vec.begin(), vec.end());
    auto end = std::chrono::system_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    return time.count();
}