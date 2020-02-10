#pragma once
#include <iostream>
#include <cstdarg>
#include <array>
#include <gtest/gtest.h>
using std::cout;
using std:: endl;

// message

/**
\Выводит на заданный поток строку, получаемой из шаблона со вставкой заданных элементов вместо %
\param[in] stream Заданный поток
\param[in] format Заданный шаблон
\param[in] Other Элементы, которые нужно вставить на место %
*/

void message(std::ostream& &stream, const char *format) {}

template<typename First, typename ... Other>
void message(std::ostream &stream, const char *format, First&& first, Other&& ... other) {
    while (*format ) {
        if (*format == '%') {
            stream << first;
            format++;
            return message(stream, format, other...);
        }
        stream << *(format++);
    }
}

// cat
template <class T, size_t N, class ... Arrs>
auto cat(std::array<T, N>& first, Arrs&& ... other) -> std::array<T, (sizeof...(other) + 1) * N>
{
    std::array<std::array<T, N>, N> arr = { std::forward<Arrs>(other)... };
    std::array<T, (sizeof ... (other) + 1) * N> res;
    std::copy(first.cbegin(), first.cend(), res.begin());
    for (int i = 0; i < sizeof ... (other); ++i) {
        std::copy(arr[i].cbegin(), arr[i].cend(), res.begin() + (i + 1) * N);
    }
    return res;
}


// tie
template<class T,int N,int M>
struct Tie {
    std::array<T*, M> tuple;
    Tie(std::array<T*, M> arr)
            : tuple(arr)
    {}
    void operator=(const std::array<T, N * M>& rhs) {
        for(int i = 0; i < M; ++i) {
            std::copy(rhs.cbegin() + (i * N) , rhs.cbegin() + (i + 1) *  N, tuple[i]);
        }
    }
};


template<class T, size_t N, class... Arrs>
auto tie(std::array<T, N> & first, Arrs&& ... other) -> Tie<T, N, sizeof ... (other) + 1> {
    std::array<T*, sizeof ... (other) + 1> arr {first.data(), std::forward<Arrs>(other).data() ...};
    return Tie<T, N, sizeof ... (other) + 1>(arr);
}