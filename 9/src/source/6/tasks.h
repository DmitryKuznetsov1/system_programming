#pragma once
#include <iostream>
#include <cmath>
#define _USE_MATH_DEFINES
#include <vector>
#include <complex>

template<typename T>
class Circle {
    T R;
public:
    Circle(const T radius)
            : R(radius)
    {}

    ~Circle() {}

    T radius() {
        return R;
    }

    T square() {
        return M_PI * (R * R);
    }
};


template<typename T>
class Rectangle {
    T lenth;
    T width;
public:
    Rectangle(const T _lenth, const T _width)
            : lenth(_lenth)
            , width(_width)
    {}

    ~Rectangle() {}

    T getLenth() {
        return lenth;
    }

    T getWidth() {
        return width;
    }

    T square() {
        return lenth * width;
    }
};


namespace std {
    template<class T>
    struct Trait {
        static size_t size(T &elem) {
            return sizeof(elem);
        }
    };

    template<typename T>
    struct Trait<Circle<T> > {
        static size_t size(Circle<T> &circle) {
            return sizeof(circle.radius());
        }
    };

    template<typename T>
    struct Trait<Rectangle<T> > {
        static size_t size(Rectangle<T> &rect) {
            return sizeof(rect.getLenth() + rect.getWidth());
        }
    };
}

template<typename T>
class Polynomial{
public:
    size_t deg;
    std::vector<T> coeffs;
//    std::vector<std::string> signs;
public:
    // defaul constructor
    Polynomial() {this->coeffs = {}; deg = 0;}

    //constructor from initializer list
    Polynomial(std::initializer_list<T> _coeffs)
            : deg(_coeffs.size())
    {
        for (auto &coef : _coeffs) {
            coeffs.push_back(coef);
        }
    }

    // constructor from vector
    Polynomial(std::vector<T> vec)
            : deg(vec.size())
    {
        for (auto& coef : vec) {
            coeffs.push_back(coef);
        }
    }

    // destructor
    ~Polynomial() {
        coeffs.clear();
    }

    // add signs
    std::vector<std::string> add_signs() {
        std::vector<std::string> signs;
        for (auto& coef: coeffs) {
            if (coef > 0)
                signs.push_back(" + ");
            else
                signs.push_back(" - ");
        }
        return signs;
    }

    //push back
    void push_back(T value) {
        this->coeffs.push_back(value);
        this->deg += 1;

    }

    // operator -
    Polynomial<T> operator- (Polynomial<T> other) {
        Polynomial<T> res;
        for (size_t i = 0; i < std::max(other.deg, this->deg); ++i)
            res.push_back(this->coeffs[i] - other.coeffs[i]);
        return res;
    }

    // operator *
    Polynomial<T> operator* (T constant) {
        Polynomial<T> res;
        for (size_t i = 0; i < deg; ++i)
            res.push_back(coeffs[i] * constant);
        return res;
    }

    // representation of polynom
    void show() {
        std::cout << "degree: " << deg - 1 << '\n';
        std::vector<std::string> signs = this->add_signs();
        for (size_t i = deg - 1; i!= 0; --i) {
            std::cout << signs[i] << abs(coeffs[i]) << "x^" << i;
        }
        std::cout << signs[0] << abs(coeffs[0]) << '\n';
    }

    void show_c() {
        for (size_t i = deg - 1; i!= 0; --i) {
            std::cout << coeffs[i] << "x^" << i << " ";
        }
        std::cout << coeffs[0] << '\n';
    }
};

//reciprocal
template<typename T>
Polynomial<T> reciprocal(Polynomial<T> &poly) {
    Polynomial<T> res;
    for (size_t i = 0; i < poly.deg; ++i) {
        res.push_back(std::conj(poly.coeffs[i]));
    }
    return res;
}


template<typename T>
Polynomial<std::complex<T> > reciprocal(Polynomial<std::complex<T> > &poly) {
    Polynomial<std::complex<T> > res;
    for (size_t i = 0; i < poly.deg; ++i) {
        res.push_back(std::conj(poly.coeffs[i]));
    }
    return res;
}


template<typename T>
struct is_complex_t : public std::false_type {};

template<typename T>
struct is_complex_t<std::complex<T>> : public std::true_type {};


// Schur transform for arithmetic
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, Polynomial<T>>::type
Schur(Polynomial<T> poly) {
    return (poly * poly.coeffs[0] ) - (poly * poly.coeffs[poly.deg - 1]);
}

// Schur transform for complex
template<typename T>
typename std::enable_if<is_complex_t<T>::value, Polynomial<T>>::type
Schur(Polynomial<T> poly) {
    Polynomial<T> polyR = reciprocal(poly);
    return (poly * std::conj(poly.coeffs[0])) - (polyR * poly.coeffs[poly.deg - 1]);
}
