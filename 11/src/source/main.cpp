#include <iostream>
#include <vector>
#include "MergeSortThreads.h"


int main() {
    std::vector<long> time_simple, time_thread, vec_sizes;
    std::vector<int> vector = {0, 10, 16, 1, 4, 2, 5, 3};
    merge_sort_parallel(vector);
    for (int i = 0; i < vector.size(); i++) {
            std::cout << vector[i] << '\n';
    }
//    time_thread.push_back(merge_sort_parallel(vector));
//    merge_sort_parallel(vector);
//    for (size_t size = 10; size < 100; size *= 10) {
//        std::vector<int> vector(size);
//
//        for (int i = 0; i < size; i++) {
//            vector[i] = rand();
//        }
//
//        vec_sizes.push_back(size);
//        time_thread.push_back(merge_sort_parallel(vector));
//        time_simple.push_back(merge_sort(vector));
//    }

//    for (size_t i = 0; i < vec_sizes.size(); ++i) {
//        std::cout << "vector size = " << vec_sizes[i] << '\n' << "time:\n" << time_simple[i] << " and " << time_thread[i] << '\n';
//    }
    return 0;

}
