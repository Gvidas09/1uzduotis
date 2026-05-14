#pragma once
#include <cstddef>
#include <initializer_list>

template<typename T>
class Vector {
public:
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    ~Vector() {
        delete[] data_;
    }

    explicit Vector(size_t n, const T& val = T{})
        : data_(new T[n]), size_(n), capacity_(n) {
        for (size_t i = 0; i < n; ++i)
            data_[i] = val;
    }

    Vector(std::initializer_list<T> il)
        : data_(new T[il.size()]), size_(il.size()), capacity_(il.size()) {
        size_t i = 0;
        for (const T& val : il)
            data_[i++] = val;
    }

private:
    T*     data_;
    size_t size_;
    size_t capacity_;
};
