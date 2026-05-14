#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "Vector.h"
#include <algorithm>
#include <type_traits>

// ---------------------------------------------------------------------------
// Konstruktoriai
// ---------------------------------------------------------------------------

TEST_CASE("Numatytasis konstruktorius") {
    Vector<int> v;
    CHECK(v.size()     == 0);
    CHECK(v.capacity() == 0);
    CHECK(v.empty());
}

TEST_CASE("Konstruktorius su dydziu ir reiksme") {
    Vector<int> v(5, 42);
    CHECK(v.size()     == 5);
    CHECK(v.capacity() == 5);
    CHECK_FALSE(v.empty());
    for (size_t i = 0; i < v.size(); ++i)
        CHECK(v[i] == 42);
}

TEST_CASE("Konstruktorius su dydziu - numatyta reiksme") {
    Vector<int> v(3);
    CHECK(v.size() == 3);
    for (size_t i = 0; i < v.size(); ++i)
        CHECK(v[i] == 0);
}

TEST_CASE("Initializer_list konstruktorius") {
    Vector<int> v = {1, 2, 3, 4, 5};
    CHECK(v.size() == 5);
    CHECK(v[0] == 1);
    CHECK(v[4] == 5);
}

// ---------------------------------------------------------------------------
// Rule of Five
// ---------------------------------------------------------------------------

TEST_CASE("Kopijavimo konstruktorius - gili kopija") {
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2(v1);
    CHECK(v2.size() == 3);
    CHECK(v2[0] == 1);
    CHECK(v2[2] == 3);
    v2[0] = 99;
    CHECK(v1[0] == 1);
}

TEST_CASE("Perkelimo konstruktorius") {
    Vector<int> v1 = {10, 20, 30};
    Vector<int> v2(std::move(v1));
    CHECK(v2.size() == 3);
    CHECK(v2[0] == 10);
    CHECK(v1.size()     == 0);
    CHECK(v1.capacity() == 0);
    CHECK(v1.empty());
}

TEST_CASE("Kopijavimo priskyrimas - gili kopija") {
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2;
    v2 = v1;
    CHECK(v2.size() == 3);
    CHECK(v2[1] == 2);
    v2[1] = 99;
    CHECK(v1[1] == 2);
}

TEST_CASE("Kopijavimo priskyrimas sau") {
    Vector<int> v = {1, 2, 3};
    v = v;
    CHECK(v.size() == 3);
    CHECK(v[0] == 1);
    CHECK(v[2] == 3);
}

TEST_CASE("Perkelimo priskyrimas") {
    Vector<int> v1 = {5, 6, 7};
    Vector<int> v2;
    v2 = std::move(v1);
    CHECK(v2.size() == 3);
    CHECK(v2[0] == 5);
    CHECK(v1.size()  == 0);
    CHECK(v1.empty());
}

TEST_CASE("Destruktorius - nemetantis") {
    CHECK(std::is_nothrow_destructible<Vector<int>>::value);
}

// ---------------------------------------------------------------------------
// push_back, pop_back, size, capacity
// ---------------------------------------------------------------------------

TEST_CASE("push_back didina size") {
    Vector<int> v;
    CHECK(v.size() == 0);
    v.push_back(1);
    CHECK(v.size() == 1);
    v.push_back(2);
    CHECK(v.size() == 2);
    v.push_back(3);
    CHECK(v.size() == 3);
}

TEST_CASE("push_back issaugo reiksmes") {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    CHECK(v[0] == 10);
    CHECK(v[1] == 20);
    CHECK(v[2] == 30);
}

TEST_CASE("push_back capacity dvigubejimas") {
    Vector<int> v;
    CHECK(v.capacity() == 0);
    v.push_back(1);
    CHECK(v.capacity() == 1);
    v.push_back(2);
    CHECK(v.capacity() == 2);
    v.push_back(3);
    CHECK(v.capacity() == 4);
    v.push_back(4);
    CHECK(v.capacity() == 4);
    v.push_back(5);
    CHECK(v.capacity() == 8);
}

TEST_CASE("pop_back mazina size") {
    Vector<int> v = {1, 2, 3};
    CHECK(v.size() == 3);
    v.pop_back();
    CHECK(v.size() == 2);
    v.pop_back();
    CHECK(v.size() == 1);
}

TEST_CASE("pop_back issaugo likusius elementus") {
    Vector<int> v = {10, 20, 30};
    v.pop_back();
    CHECK(v[0] == 10);
    CHECK(v[1] == 20);
}

TEST_CASE("pop_back ant tusto vektoriaus nekrinta") {
    Vector<int> v;
    v.pop_back();
    CHECK(v.size() == 0);
}

TEST_CASE("push_back po pop_back") {
    Vector<int> v = {1, 2, 3};
    v.pop_back();
    v.push_back(99);
    CHECK(v.size() == 3);
    CHECK(v[2] == 99);
}

// ---------------------------------------------------------------------------
// reserve, resize
// ---------------------------------------------------------------------------

TEST_CASE("reserve padidina capacity") {
    Vector<int> v;
    v.reserve(10);
    CHECK(v.capacity() == 10);
    CHECK(v.size()     == 0);
    CHECK(v.empty());
}

TEST_CASE("reserve nemažina capacity") {
    Vector<int> v;
    v.reserve(10);
    v.reserve(5);
    CHECK(v.capacity() == 10);
}

TEST_CASE("reserve nekeicia elementu") {
    Vector<int> v = {1, 2, 3};
    v.reserve(20);
    CHECK(v.size() == 3);
    CHECK(v[0] == 1);
    CHECK(v[2] == 3);
}

TEST_CASE("resize padidina su numatyta reiksme") {
    Vector<int> v = {1, 2};
    v.resize(5, 99);
    CHECK(v.size() == 5);
    CHECK(v[0] == 1);
    CHECK(v[2] == 99);
    CHECK(v[4] == 99);
}

TEST_CASE("resize sumazina") {
    Vector<int> v = {1, 2, 3, 4, 5};
    v.resize(2);
    CHECK(v.size() == 2);
    CHECK(v[0] == 1);
    CHECK(v[1] == 2);
}

// ---------------------------------------------------------------------------
// operator[], at, front, back, data
// ---------------------------------------------------------------------------

TEST_CASE("operator[] skaito ir raso") {
    Vector<int> v = {10, 20, 30};
    CHECK(v[0] == 10);
    v[1] = 99;
    CHECK(v[1] == 99);
}

TEST_CASE("at meta out_of_range") {
    Vector<int> v = {1, 2, 3};
    CHECK_THROWS_AS(v.at(3),  std::out_of_range);
    CHECK_THROWS_AS(v.at(10), std::out_of_range);
    CHECK_NOTHROW(v.at(2));
}

TEST_CASE("front ir back") {
    Vector<int> v = {5, 10, 15};
    CHECK(v.front() == 5);
    CHECK(v.back()  == 15);
    v.front() = 99;
    CHECK(v[0] == 99);
    v.back() = 77;
    CHECK(v[2] == 77);
}

TEST_CASE("data grąžina teisingą rodyklę") {
    Vector<int> v = {1, 2, 3};
    int* p = v.data();
    CHECK(p[0] == 1);
    p[1] = 42;
    CHECK(v[1] == 42);
}

// ---------------------------------------------------------------------------
// begin, end, iteratoriai
// ---------------------------------------------------------------------------

TEST_CASE("begin ir end range-for") {
    Vector<int> v = {1, 2, 3, 4, 5};
    int suma = 0;
    for (int x : v) suma += x;
    CHECK(suma == 15);
}

TEST_CASE("begin ir end su std::sort") {
    Vector<int> v = {5, 3, 1, 4, 2};
    std::sort(v.begin(), v.end());
    CHECK(v[0] == 1);
    CHECK(v[4] == 5);
}

TEST_CASE("cbegin ir cend - const iteratoriai") {
    const Vector<int> v = {10, 20, 30};
    int suma = 0;
    for (auto it = v.cbegin(); it != v.cend(); ++it)
        suma += *it;
    CHECK(suma == 60);
}

// ---------------------------------------------------------------------------
// insert
// ---------------------------------------------------------------------------

TEST_CASE("insert pradžioje") {
    Vector<int> v = {2, 3, 4};
    auto it = v.insert(v.begin(), 1);
    CHECK(v.size() == 4);
    CHECK(v[0] == 1);
    CHECK(v[1] == 2);
    CHECK(*it == 1);
}

TEST_CASE("insert pabaigoje") {
    Vector<int> v = {1, 2, 3};
    auto it = v.insert(v.end(), 4);
    CHECK(v.size() == 4);
    CHECK(v[3] == 4);
    CHECK(*it == 4);
}

TEST_CASE("insert viduryje") {
    Vector<int> v = {1, 3, 4};
    auto it = v.insert(v.begin() + 1, 2);
    CHECK(v.size() == 4);
    CHECK(v[0] == 1);
    CHECK(v[1] == 2);
    CHECK(v[2] == 3);
    CHECK(*it == 2);
}

TEST_CASE("insert i tuščią vektorių") {
    Vector<int> v;
    auto it = v.insert(v.begin(), 42);
    CHECK(v.size() == 1);
    CHECK(v[0] == 42);
    CHECK(*it == 42);
}

TEST_CASE("insert su perskirstymu") {
    Vector<int> v = {1, 2, 3};
    v.reserve(3);
    v.insert(v.begin(), 0);
    CHECK(v.size() == 4);
    CHECK(v[0] == 0);
    CHECK(v[1] == 1);
}

// ---------------------------------------------------------------------------
// erase
// ---------------------------------------------------------------------------

TEST_CASE("erase pirmą elementą") {
    Vector<int> v = {1, 2, 3};
    auto it = v.erase(v.begin());
    CHECK(v.size() == 2);
    CHECK(v[0] == 2);
    CHECK(*it == 2);
}

TEST_CASE("erase paskutinį elementą") {
    Vector<int> v = {1, 2, 3};
    auto it = v.erase(v.end() - 1);
    CHECK(v.size() == 2);
    CHECK(v[1] == 2);
    CHECK(it == v.end());
}

TEST_CASE("erase viduryje") {
    Vector<int> v = {1, 2, 3, 4};
    auto it = v.erase(v.begin() + 1);
    CHECK(v.size() == 3);
    CHECK(v[0] == 1);
    CHECK(v[1] == 3);
    CHECK(*it == 3);
}

TEST_CASE("erase iki tuščio") {
    Vector<int> v = {1, 2, 3};
    v.erase(v.begin());
    v.erase(v.begin());
    v.erase(v.begin());
    CHECK(v.size() == 0);
    CHECK(v.empty());
}
