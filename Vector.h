#pragma once
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

template<typename T>
class Vector {
public:
    using value_type     = T;
    using iterator       = T*;
    using const_iterator = const T*;

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

    size_t size()     const noexcept { return size_; }
    size_t capacity() const noexcept { return capacity_; }
    bool   empty()    const noexcept { return size_ == 0; }

    void clear() noexcept { size_ = 0; }

    T&       front()       { return data_[0]; }
    const T& front() const { return data_[0]; }
    T&       back()        { return data_[size_ - 1]; }
    const T& back()  const { return data_[size_ - 1]; }

    T*       data()       noexcept { return data_; }
    const T* data() const noexcept { return data_; }

    iterator       begin()        noexcept { return data_; }
    iterator       end()          noexcept { return data_ + size_; }
    const_iterator begin()  const noexcept { return data_; }
    const_iterator end()    const noexcept { return data_ + size_; }
    const_iterator cbegin() const noexcept { return data_; }
    const_iterator cend()   const noexcept { return data_ + size_; }

    T&       operator[](size_t i)       { return data_[i]; }
    const T& operator[](size_t i) const { return data_[i]; }

    T& at(size_t i) {
        if (i >= size_) throw std::out_of_range("Vector::at: indeksas uz ribo");
        return data_[i];
    }
    const T& at(size_t i) const {
        if (i >= size_) throw std::out_of_range("Vector::at: indeksas uz ribo");
        return data_[i];
    }

    void shrink_to_fit() {
        if (size_ < capacity_)
            reallocate(size_);
    }

    void push_back(const T& val) {
        if (size_ >= capacity_)
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        data_[size_++] = val;
    }

    void push_back(T&& val) {
        if (size_ >= capacity_)
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        data_[size_++] = std::move(val);
    }

    void pop_back() {
        if (size_ > 0)
            --size_;
    }

    iterator insert(iterator pos, const T& val) {
        size_t idx = static_cast<size_t>(pos - data_);
        if (size_ >= capacity_)
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        pos = data_ + idx;
        for (size_t i = size_; i > idx; --i)
            data_[i] = std::move(data_[i - 1]);
        data_[idx] = val;
        ++size_;
        return data_ + idx;
    }

    void reserve(size_t n) {
        if (n > capacity_)
            reallocate(n);
    }

    void resize(size_t n, const T& val = T{}) {
        if (n > capacity_)
            reallocate(n);
        for (size_t i = size_; i < n; ++i)
            data_[i] = val;
        size_ = n;
    }

private:
    T*     data_;
    size_t size_;
    size_t capacity_;

    void reallocate(size_t new_cap) {
        T* new_data = new T[new_cap];
        for (size_t i = 0; i < size_; ++i)
            new_data[i] = std::move(data_[i]);
        delete[] data_;
        data_     = new_data;
        capacity_ = new_cap;
    }
};
