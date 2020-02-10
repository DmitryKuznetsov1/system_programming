#pragma once
#include <iostream>
#include <vector>
#include <iterator>
#include <unordered_map>
#include <map>
#include <set>
#include <unordered_set>

template<class T>
class  outIterator {
    std::ostream *stream;
    size_t N;
    const char* delim;
    size_t counter = 0;
public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::output_iterator_tag;
    // initialization
    outIterator(std::ostream& out)
            : stream(&out)
            , N(1)
            , delim(" ")
    {}

    outIterator(std::ostream& out, size_t N, const char* delimiter)
            : stream(&out)
            , N(N)
            , delim(delimiter)
    {}
    // =
    outIterator<T>& operator= (const T& value) {
        if (counter % N == 0){
            *stream << value << delim;
        }
        return *this;
    }
    // destructor
    ~outIterator() {}

    outIterator<T>& operator* () {
        return *this;
    }

    outIterator<T>& operator++ () {
        ++counter;
        return *this;
    }

    outIterator<T>& operator++ (int) {
        ++counter;
        return *this;
    }
};

class User {
    int id;
    std::string name;
public:
    User(int _id, std::string _name)
            : id(_id)
            , name(_name)
    {}

    int get_id() const {
        return id;
    }

    std::string get_name() const {
        return name;
    }

    bool operator==(const User &other) const {
        return (id == other.id && name == other.name);
    }

    bool operator<(const User& other) const {
        return (this->get_id() < other.get_id());
    }
};

namespace std {
    template <> struct hash<User> {
        size_t operator()(const User & user) const {
            return user.get_id();
        }
    };
}


#include <iterator>
#include <vector>

template<typename It>
std::vector<typename It::value_type> merge(const It begin, const It mid, const It end)
{
    std::vector<typename It::value_type> buffer;
    It left(begin);
    It right(mid);
    const It &left_end = mid;
    const It &right_end = end;

    while (left != left_end && right != right_end) {
        buffer.push_back((*left <= *right) ? std::move(*left++) : std::move(*right++));
    }

    buffer.insert(buffer.end(), left, left_end);
    buffer.insert(buffer.end(), right, right_end);

    return buffer;
}

template<typename It>
void merge_sort(It begin, It end)
{
    auto size = std::distance(begin, end);
    if (size < 2)
        return;

    auto mid = std::next(begin, size / 2);
    merge_sort(begin, mid);
    merge_sort(mid, end);

    auto &&v = merge(begin, mid, end);
    std::move(v.cbegin(), v.cend(), begin);
}




