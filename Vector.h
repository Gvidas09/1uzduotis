#pragma once
#include <cstddef>

template<typename T>
class Vector {
private:
    T*     data_;
    size_t size_;
    size_t capacity_;
};
