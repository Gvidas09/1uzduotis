#pragma once
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

/**
 * @file Vector.h
 * @brief Savas std::vector analogas su pilnu atminties valdymu.
 */

/**
 * @brief Dinaminis masyvas — std::vector atitikmuo su Rule of Five.
 *
 * Naudoja žaliuosius rodyklius ir dvigubėjimo augimo strategiją.
 * Palaiko STL iteratorių sąsają (T* rodyklės).
 *
 * @tparam T Saugomų elementų tipas.
 */
template<typename T>
class Vector {
public:
    using value_type     = T;          ///< Elemento tipas (reikalingas std::back_inserter)
    using iterator       = T*;         ///< Kintamojo iteratoriaus tipas
    using const_iterator = const T*;   ///< Pastovaus iteratoriaus tipas

    /** @brief Numatytasis konstruktorius — tuščias vektorius. */
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    /** @brief Destruktorius — atlaisvina dinamiškai skirtą atmintį. */
    ~Vector() {
        delete[] data_;
    }

    /**
     * @brief Konstruktorius su pradiniu dydžiu ir reikšme.
     * @param n    Elementų skaičius.
     * @param val  Pradinė kiekvieno elemento reikšmė (numatytoji — T{}).
     */
    explicit Vector(size_t n, const T& val = T{})
        : data_(new T[n]), size_(n), capacity_(n) {
        for (size_t i = 0; i < n; ++i)
            data_[i] = val;
    }

    /**
     * @brief Konstruktorius iš inicializavimo sąrašo.
     * @param il  Elementų sąrašas, pvz. `{1, 2, 3}`.
     */
    Vector(std::initializer_list<T> il)
        : data_(new T[il.size()]), size_(il.size()), capacity_(il.size()) {
        size_t i = 0;
        for (const T& val : il)
            data_[i++] = val;
    }

    /**
     * @brief Kopijavimo konstruktorius — gili kopija.
     * @param other  Kopijuojamas vektorius.
     */
    Vector(const Vector& other)
        : data_(new T[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
        for (size_t i = 0; i < size_; ++i)
            data_[i] = other.data_[i];
    }

    /**
     * @brief Perkėlimo konstruktorius — perima kito vektoriaus išteklius.
     * @param other  Perkeliamas vektorius (po to — tuščias).
     */
    Vector(Vector&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_     = nullptr;
        other.size_     = 0;
        other.capacity_ = 0;
    }

    /**
     * @brief Apsikeitimas su kitu vektoriumi be išimčių.
     * @param other  Vektorius, su kuriuo apsikeičiama.
     */
    void swap(Vector& other) noexcept {
        std::swap(data_,     other.data_);
        std::swap(size_,     other.size_);
        std::swap(capacity_, other.capacity_);
    }

    /**
     * @brief Kopijavimo priskyrimo operatorius (copy-and-swap).
     * @param other  Priskiriamas vektorius.
     * @return Nuoroda į save.
     */
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector tmp(other);
            swap(tmp);
        }
        return *this;
    }

    /**
     * @brief Perkėlimo priskyrimo operatorius.
     * @param other  Perkeliamas vektorius.
     * @return Nuoroda į save.
     */
    Vector& operator=(Vector&& other) noexcept {
        swap(other);
        return *this;
    }

    /** @brief Grąžina elementų skaičių. */
    size_t size()     const noexcept { return size_; }

    /** @brief Grąžina dabartinę talpą (be perskirstymo). */
    size_t capacity() const noexcept { return capacity_; }

    /** @brief Tikrina, ar vektorius tuščias. */
    bool   empty()    const noexcept { return size_ == 0; }

    /** @brief Išvalo vektorių (nenaikina atminties). */
    void clear() noexcept { size_ = 0; }

    /** @brief Grąžina nuorodą į pirmą elementą. */
    T&       front()       { return data_[0]; }
    /** @brief Grąžina pastovią nuorodą į pirmą elementą. */
    const T& front() const { return data_[0]; }

    /** @brief Grąžina nuorodą į paskutinį elementą. */
    T&       back()        { return data_[size_ - 1]; }
    /** @brief Grąžina pastovią nuorodą į paskutinį elementą. */
    const T& back()  const { return data_[size_ - 1]; }

    /** @brief Grąžina žaliąją rodyklę į duomenų masyvą. */
    T*       data()       noexcept { return data_; }
    /** @brief Grąžina pastovią žaliąją rodyklę į duomenų masyvą. */
    const T* data() const noexcept { return data_; }

    /** @brief Iteratorius į pirmą elementą. */
    iterator       begin()        noexcept { return data_; }
    /** @brief Iteratorius už paskutinio elemento. */
    iterator       end()          noexcept { return data_ + size_; }
    /** @brief Pastovus iteratorius į pirmą elementą. */
    const_iterator begin()  const noexcept { return data_; }
    /** @brief Pastovus iteratorius už paskutinio elemento. */
    const_iterator end()    const noexcept { return data_ + size_; }
    /** @brief Pastovus iteratorius į pirmą elementą. */
    const_iterator cbegin() const noexcept { return data_; }
    /** @brief Pastovus iteratorius už paskutinio elemento. */
    const_iterator cend()   const noexcept { return data_ + size_; }

    /**
     * @brief Prieiga prie elemento pagal indeksą (be patikrinimo).
     * @param i  Elemento indeksas.
     */
    T&       operator[](size_t i)       { return data_[i]; }
    /** @copydoc operator[](size_t) */
    const T& operator[](size_t i) const { return data_[i]; }

    /**
     * @brief Prieiga prie elemento su ribų patikrinimu.
     * @param i  Elemento indeksas.
     * @throws std::out_of_range  Jei `i >= size()`.
     */
    T& at(size_t i) {
        if (i >= size_) throw std::out_of_range("Vector::at: indeksas uz ribo");
        return data_[i];
    }
    /** @copydoc at(size_t) */
    const T& at(size_t i) const {
        if (i >= size_) throw std::out_of_range("Vector::at: indeksas uz ribo");
        return data_[i];
    }

    /**
     * @brief Sumažina talpą iki dabartinio dydžio.
     */
    void shrink_to_fit() {
        if (size_ < capacity_)
            reallocate(size_);
    }

    /**
     * @brief Prideda elementą į pabaigą (kopijavimas).
     * @param val  Pridedama reikšmė.
     */
    void push_back(const T& val) {
        if (size_ >= capacity_)
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        data_[size_++] = val;
    }

    /**
     * @brief Prideda elementą į pabaigą (perkėlimas).
     * @param val  Perkeliama reikšmė.
     */
    void push_back(T&& val) {
        if (size_ >= capacity_)
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        data_[size_++] = std::move(val);
    }

    /** @brief Pašalina paskutinį elementą. Nieko nedaro, jei vektorius tuščias. */
    void pop_back() {
        if (size_ > 0)
            --size_;
    }

    /**
     * @brief Pašalina elementą nurodytoje pozicijoje.
     * @param pos  Iteratorius į šalinamą elementą.
     * @return Iteratorius į elementą, buvusį po pašalintojo.
     */
    iterator erase(iterator pos) {
        size_t idx = static_cast<size_t>(pos - data_);
        for (size_t i = idx; i < size_ - 1; ++i)
            data_[i] = std::move(data_[i + 1]);
        --size_;
        return data_ + idx;
    }

    /**
     * @brief Įterpia elementą prieš nurodytą poziciją.
     * @param pos  Iteratorius į poziciją, prieš kurią įterpiama.
     * @param val  Įterpiama reikšmė.
     * @return Iteratorius į įterptą elementą.
     */
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

    /**
     * @brief Užtikrina, kad talpa būtų bent `n`.
     * @param n  Minimali reikiama talpa.
     */
    void reserve(size_t n) {
        if (n > capacity_)
            reallocate(n);
    }

    /**
     * @brief Pakeičia vektoriaus dydį į `n`.
     * @param n    Naujas dydis.
     * @param val  Reikšmė naujiems elementams (numatytoji — T{}).
     */
    void resize(size_t n, const T& val = T{}) {
        if (n > capacity_)
            reallocate(n);
        for (size_t i = size_; i < n; ++i)
            data_[i] = val;
        size_ = n;
    }

private:
    T*     data_;      ///< Žalioji rodyklė į duomenų masyvą
    size_t size_;      ///< Dabartinis elementų skaičius
    size_t capacity_;  ///< Dabartinė talpa

    /** @brief Perskirstо atmintį į naują buferį su `new_cap` talpa. */
    void reallocate(size_t new_cap) {
        T* new_data = new T[new_cap];
        for (size_t i = 0; i < size_; ++i)
            new_data[i] = std::move(data_[i]);
        delete[] data_;
        data_     = new_data;
        capacity_ = new_cap;
    }
};
