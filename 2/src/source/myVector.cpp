#pragma once

#include <iostream>
#include <vector>
#include <initializer_list>

using std::cout;
using std::endl;

template<typename T>
class myVector {
private:
    T *buffer;
    size_t size_;
    size_t capacity_;

public:
    // default constructor
    myVector()
            : capacity_(0)
            , size_(0)
            , buffer(nullptr)
    {}

    // 1st constructor (empty)
    myVector(size_t capacity)
            : capacity_(capacity)
            , size_(0)
            , buffer(new T[capacity])
//            , buffer(static_cast<T*>(::operator new(sizeof(T) * capacity)))
    {
//        cout << "You've created empty vector with capacity: " << capacity_ << endl;
    }

    // 2nd constructor (by value)
    myVector(size_t N, const T &value)
            : capacity_(N)
            , size_(N)
            , buffer(static_cast<T*>(::operator new(sizeof(T) * N)))
    {
        while (N--) { buffer[N] = value; }
//        cout << "You've created vector with value: " << value << " and capacity: " << capacity_ << endl;
    }

    // constructor by list of values
    myVector(std::initializer_list<T> &list) {
        myVector(list.size());
        for (auto &value : list) {
            this->push_back(value);
        }
    }

    // destructor
    ~myVector() {
        delete [] buffer;
        capacity_ = size_ = 0;
    }

    // copy constructor
    myVector(const myVector& copy)
            : capacity_(copy.capacity_)
            , size_(0)
            , buffer(new T[copy.capacity_])
    {
        for (int i = 0; i < copy.size_; ++i) {
            push_back(copy.buffer[i]);
        }
    }

    // move constructor
    myVector(myVector&& copy)
            : capacity_(copy.capacity_)
            , size_(0)
            , buffer(new T[copy.capacity_])
    {
        for (int i = 0; i < copy.size_; ++i) {
            push_back(std::move(copy.buffer[i]));
        }
    }

    // push_back by copy
    void push_back(const T& elem) {
        if ( capacity_ > size_ ) {
            buffer[size_] = elem;
            size_++;
        } else {
            T *newBuffer = new T[capacity_ + 1];
            for (size_t i = 0; i != size_; ++i)
                newBuffer[i] = buffer[i];
            newBuffer[size_++] = elem;

            delete [] buffer;
            buffer = newBuffer;
            capacity_++;
//            cout << "You added { " << elem << " } by copying" << endl;
        }
    }

    // push_back by move
    void push_back(T&& elem) {
        if ( capacity_ > size_ ) {
            buffer[size_] = std::move(elem);
            size_++;
        } else {
            T *newBuffer = new T[capacity_ + 1];
            for (size_t i = 0; i < size_ ; i++){
                newBuffer[i] = std::move(buffer[i]);
            }
            newBuffer[size_++] = std::move(elem);

            delete [] buffer;
            buffer = newBuffer;
            capacity_++;
        }
//        cout << "You added { " << elem << " } by moving" << endl;
    }
    // pop_back
    void pop_back() {
        if ( size_ == 0 ) {
//            cout << "vector is empty" << endl;
        }
        else {
//            cout << "You removed { " << buffer[size_-1] << " }" << endl;
            buffer[size_--].~T();
        }
    }

    // erase
    T* erase(T *first, T *last) {
        T *tmp = last;

        while (last != this->end()) {
            *first = std::move(*(last++));
            first ++;
        }

        size_t k = last - first;
        while (k--) {
            this->pop_back();
        }
        return tmp;
    }
    // swap inside
    myVector<T> swap(myVector other) {
        std::swap(buffer, other.buffer);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    // = by copy
    myVector<T> &operator=(const myVector &other) {
        swap(other);
        return *this;
    }

    // = by move
    myVector<T> &operator=(myVector &&other) {
        swap(other);
        other.~myVector;
    }

    // begin, end, size
    T *begin() const { return buffer; }

    T *end() const { return buffer + size_; }

    size_t size() const { return this->size_; }

    // representation of vector
    void show() {
        cout << "capacity: " << capacity_ << endl;
        cout << "size: " << size_ << endl;
        cout << "elements: { ";
        for (T *p = buffer; p != buffer + size_; p++) {
            cout << *p << " ";
        }
        cout << "}" << endl;
    }
};


//swap outside
template<typename T>
void swap(myVector<T> &vect1, myVector<T> &vect2) {
    vect1.swap(vect2);
}