#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <math.h>


using std::cout; using std::endl;

struct MyGuard {
    std::ostream& stream_;
    std::ios_base::fmtflags flags_;
    char fill_;
    std::ios_base::iostate exceptions_;

    MyGuard(std::ostream& stream)
            : stream_(stream)
            , flags_(stream.flags())
            , fill_(stream.fill())
            , exceptions_(stream.exceptions())
    {}

    ~MyGuard() {
        this->stream_.flags(flags_);
        this->stream_.fill(fill_);
        this->stream_.exceptions(exceptions_);
    }

    MyGuard(const MyGuard&) = delete;
    MyGuard& operator=(const MyGuard&) = delete;
};


template<typename T, size_t N, size_t M>
class Matrix {
public:
    std::vector<T> data;

    // default constructor
    Matrix() {this->data = {};}

    // constructor from list
    Matrix(std::initializer_list<T>&& values) {
        if (values.size() != N * M)
            throw std::runtime_error("size error");
        for (const auto& val : values) {
            this->data.push_back(val);
        }
    }

    // destructor
    ~Matrix(){
        this->data.clear();
    }

    // =
    Matrix<T, N, M>& operator= (Matrix<T, N, M> &mat) {
//        if (N != P || M != Q)
//            throw std::runtime_error("sizes are different");
        this->data.clear();
        std::copy(mat.cbegin(), mat.cend(), this->data);
        return this;
    }
    void push_back(T value) {
        data.push_back(value);
    }

    // Matrix_1 < Matrix_2
    Matrix<T, N, M> operator< (Matrix<T, N, M> &mat) {
        Matrix<T, N, M> bool_;
        if ( this->data.size() != mat.data.size() ) {
            throw std::runtime_error("sizes are not equal");
        }
        for (size_t i = 0; i < this->data.size(); ++i) {
            bool_.push_back(this->data[i] < mat.data[i]);
        }
        return bool_;
    }

    // Matrix < eps
    Matrix<T, N, M> operator< (double eps) {
        Matrix<T, N, M> res;
        for (int i = 0; i < this->data.size(); ++i) {
            res.push_back(this->data[i] < eps);
        }
        return res;
    }

    bool operator==(const Matrix<T, N, M> &mat){
        for (size_t i = 0; i < N * M; i++)
            if (this->data[i] != mat.data[i])
                return false;
        return true;
    }

    // transpose
    Matrix<T, M, N> transposed() const {
        Matrix<T, M, N> newMat;
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                newMat.push_back(this->data[i + j * M]);
            }
        }
        return newMat;
    }

    // -
    Matrix<T, N, M> operator- (const Matrix<T, N, M> mat) const {
        Matrix<T, N, M> res;
        for (int i = 0; i < this->data.size(); ++i) {
            res.push_back(this->data[i] - mat.data[i]);
        }
        return res;
    }
    //representation of Matrix
    void show() {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                cout << this->data[j + i * N] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // is symmetric
    bool is_symmetric(double eps = 10e-5) const
    {
        return all(absMat(*this - this->transposed()) < eps);
    }
};


template<typename T, size_t N, size_t M>
Matrix<T, N, M> where(Matrix<T, N, M> bool_, const Matrix<T, N, M> &mat1, const Matrix<T, N, M> &mat2) {
    Matrix<T, N, M> mat;
    for (size_t i = 0; i < N * M; ++i) {
        mat.push_back(bool_.data[i] ? mat1.data[i] : mat2.data[i]);
    }
    return mat;
}

template<typename T, size_t N, size_t M>
Matrix<T, N, M> absMat(const Matrix<T, N, M> mat) {
    Matrix<T, N, M> res;
    for (size_t i = 0; i < mat.data.size(); ++i) {
        res.push_back(abs(mat.data[i]));
    }
    return res;
}

template <typename T, size_t N, size_t M>
bool all(Matrix<T, N, M> boolMat) {
    for (size_t i = 0; i < boolMat.data.size(); ++i) {
        if (boolMat.data[i] == false)
            return false;
    }
    return true;
}
