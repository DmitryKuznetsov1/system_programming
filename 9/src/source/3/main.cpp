#include <iostream>
#include "c_m_t.h"

int main()
{
    std::array<float, 3> vec1{1.0f, 2.0f, 3.0f};
    std::array<float, 3> vec2{4.0f, 5.0f, 6.0f};
    std::array<float, 6> r = cat(vec1, vec2);

    std::array<float, 6> answer{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
    for (size_t i = 0; i < answer.size(); ++i) {
        std::cout << answer[i] << " and " << r[i] << '\n';
    }
    return 0;
}