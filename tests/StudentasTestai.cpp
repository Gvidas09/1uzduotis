#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "Studentas.h"
#include <sstream>
#include <type_traits>

// ---------------------------------------------------------------------------
// Konstruktoriai ir Rule of Five
// ---------------------------------------------------------------------------

TEST_CASE("Numatytasis konstruktorius") {
    Studentas s;
    CHECK(s.vardas().empty());
    CHECK(s.pavarde().empty());
    CHECK(s.pazymiai().empty());
    CHECK(s.egzaminas() == 0);
    CHECK(s.galutinisVid() == doctest::Approx(0.0));
    CHECK(s.galutinisMed() == doctest::Approx(0.0));
}

TEST_CASE("Konstruktorius su parametrais") {
    Studentas s("Jonas", "Jonaitis", {8, 9, 10}, 9);
    CHECK(s.vardas() == "Jonas");
    CHECK(s.pavarde() == "Jonaitis");
    CHECK(s.egzaminas() == 9);
    CHECK(s.pazymiai().size() == 3);
}

TEST_CASE("Konstruktorius su parametrais - netinkamas pazymys") {
    CHECK_THROWS(Studentas("Jonas", "Jonaitis", {8, 11, 10}, 9));
    CHECK_THROWS(Studentas("Jonas", "Jonaitis", {8, 9, 10}, 0));
}

TEST_CASE("Kopijavimo konstruktorius") {
    Studentas a("Ona", "Onaite", {7, 8, 9}, 10);
    Studentas b(a);
    CHECK(b.vardas() == a.vardas());
    CHECK(b.pavarde() == a.pavarde());
    CHECK(b.pazymiai() == a.pazymiai());
    CHECK(b.egzaminas() == a.egzaminas());
    CHECK(b.galutinisVid() == doctest::Approx(a.galutinisVid()));
    CHECK(b.galutinisMed() == doctest::Approx(a.galutinisMed()));
}

TEST_CASE("Kopijavimo konstruktorius - nepriklausoma kopija") {
    Studentas a("Ona", "Onaite", {7, 8, 9}, 10);
    Studentas b(a);
    b.nustatytiEgzamina(1);
    CHECK(a.egzaminas() == 10);
}

TEST_CASE("Perkelimo konstruktorius") {
    Studentas a("Petras", "Petraitis", {6, 7, 8}, 9);
    Studentas b(std::move(a));
    CHECK(b.vardas() == "Petras");
    CHECK(b.pavarde() == "Petraitis");
    CHECK(b.egzaminas() == 9);
    CHECK(a.vardas().empty());
    CHECK(a.pavarde().empty());
    CHECK(a.pazymiai().empty());
}

TEST_CASE("Kopijavimo priskyrimo operatorius") {
    Studentas a("Ieva", "Ievaite", {10, 9, 8}, 9);
    Studentas b;
    b = a;
    CHECK(b.vardas() == a.vardas());
    CHECK(b.pavarde() == a.pavarde());
    CHECK(b.pazymiai() == a.pazymiai());
    CHECK(b.egzaminas() == a.egzaminas());
}

TEST_CASE("Kopijavimo priskyrimas - priskirimas sau") {
    Studentas a("Ieva", "Ievaite", {10, 9, 8}, 9);
    a = a;
    CHECK(a.vardas() == "Ieva");
    CHECK(a.egzaminas() == 9);
}

TEST_CASE("Perkelimo priskyrimo operatorius") {
    Studentas a("Matas", "Matutis", {5, 6, 7}, 8);
    Studentas b;
    b = std::move(a);
    CHECK(b.vardas() == "Matas");
    CHECK(b.pavarde() == "Matutis");
    CHECK(a.vardas().empty());
    CHECK(a.pavarde().empty());
    CHECK(a.pazymiai().empty());
}

TEST_CASE("Destruktorius") {
    CHECK_NOTHROW([] {
        Studentas* s = new Studentas("Tomas", "Tomaitis", {8, 9, 10}, 9);
        delete s;
    }());
}

// ---------------------------------------------------------------------------
// Zmogus abstrakti klase ir paveldimumas
// ---------------------------------------------------------------------------

TEST_CASE("Zmogus yra abstrakti klase") {
    CHECK(std::is_abstract<Zmogus>::value);
}

TEST_CASE("Studentas paveldi Zmogus duomenis") {
    Studentas s("Jonas", "Jonaitis", {8, 9, 10}, 9);
    Zmogus* z = &s;
    CHECK(z->vardas() == "Jonas");
    CHECK(z->pavarde() == "Jonaitis");
}
