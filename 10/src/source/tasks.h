#pragma once
#include <iostream>
#include <vector>
#include <math.h>

template <typename T>
bool rotate(std::vector<T> &vec, double times) {
    if ( vec.size() > 2) {
        std::cout << "vector size != 2" << '\n';
        return false;
    }

    if ( times != round(times)) {
        std::cout << "number is not integer" << '\n';
        return false;
    }

    int real_times = (int)times % 4;
    if (times < 0 )
        real_times += 4;
    float x = vec[0];
    float y = vec[1];
    switch(real_times)
    {
        case 0: break;
        case 1: vec[0] = -y; vec[1] = x; return true;
        case 2: vec[0] = -x; vec[1] = -y; return true;
        case 3: vec[0] = y; vec[1] = -x; return true;
        default:
            return false;
    }
    return 0;
}