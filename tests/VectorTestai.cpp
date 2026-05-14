#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "Vector.h"
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
