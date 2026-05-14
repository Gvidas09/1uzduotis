#pragma once
#include <cstddef>
#include <initializer_list>
#include <utility>

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

    Vector(const Vector& other)
        : data_(new T[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
        for (size_t i = 0; i < size_; ++i)
            data_[i] = other.data_[i];
    }

    Vector(Vector&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_     = nullptr;
        other.size_     = 0;
        other.capacity_ = 0;
    }

    void swap(Vector& other) noexcept {
        std::swap(data_,     other.data_);
        std::swap(size_,     other.size_);
        std::swap(capacity_, other.capacity_);
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector tmp(other);
            swap(tmp);
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        swap(other);
        return *this;
    }

private:
    T*     data_;
    size_t size_;
    size_t capacity_;
};
