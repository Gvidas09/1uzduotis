#pragma once
#include <cstddef>

template<typename T>
class Vector {
public:
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    ~Vector() {
        delete[] data_;
    }

private:
    T*     data_;
    size_t size_;
    size_t capacity_;
};
