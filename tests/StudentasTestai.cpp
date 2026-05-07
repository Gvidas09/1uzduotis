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

// ---------------------------------------------------------------------------
// Skaičiavimai
// ---------------------------------------------------------------------------

TEST_CASE("Vidurkis - lyginis skaičius pazymiu") {
    Studentas s("A", "B", {6, 8}, 10);
    // vidurkis = 7.0, galutinis = 0.4*7 + 0.6*10 = 2.8 + 6.0 = 8.8
    CHECK(s.galutinisVid() == doctest::Approx(8.8));
}

TEST_CASE("Vidurkis - nelyginis skaičius pazymiu") {
    Studentas s("A", "B", {6, 8, 10}, 7);
    // vidurkis = 8.0, galutinis = 0.4*8 + 0.6*7 = 3.2 + 4.2 = 7.4
    CHECK(s.galutinisVid() == doctest::Approx(7.4));
}

TEST_CASE("Mediana - lyginis skaičius pazymiu") {
    Studentas s("A", "B", {6, 8}, 10);
    // mediana = (6+8)/2 = 7.0, galutinis = 0.4*7 + 0.6*10 = 8.8
    CHECK(s.galutinisMed() == doctest::Approx(8.8));
}

TEST_CASE("Mediana - nelyginis skaičius pazymiu") {
    Studentas s("A", "B", {6, 10, 8}, 5);
    // surikiuota: {6,8,10}, mediana = 8, galutinis = 0.4*8 + 0.6*5 = 3.2 + 3.0 = 6.2
    CHECK(s.galutinisMed() == doctest::Approx(6.2));
}

TEST_CASE("Galutinis balo formula: 0.4*ND + 0.6*egz") {
    Studentas s("A", "B", {10}, 10);
    CHECK(s.galutinisVid() == doctest::Approx(10.0));
    CHECK(s.galutinisMed() == doctest::Approx(10.0));
}

TEST_CASE("Galutinis perskaiciuojamas po nustatytiEgzamina") {
    Studentas s("A", "B", {10}, 5);
    double senas = s.galutinisVid();
    s.nustatytiEgzamina(10);
    CHECK(s.galutinisVid() > senas);
}

TEST_CASE("Galutinis perskaiciuojamas po nustatytiPazymius") {
    Studentas s("A", "B", {1}, 5);
    s.nustatytiPazymius({10, 10, 10});
    CHECK(s.galutinisVid() > 5.0);
}

// ---------------------------------------------------------------------------
// Validacija
// ---------------------------------------------------------------------------

TEST_CASE("arTinkamasPazymys - ribines reiksmes") {
    CHECK(Studentas::arTinkamasPazymys(1));
    CHECK(Studentas::arTinkamasPazymys(10));
    CHECK_FALSE(Studentas::arTinkamasPazymys(0));
    CHECK_FALSE(Studentas::arTinkamasPazymys(11));
}

TEST_CASE("nustatytiEgzamina - netinkamas pazymys") {
    Studentas s("A", "B", {5}, 5);
    CHECK_THROWS(s.nustatytiEgzamina(0));
    CHECK_THROWS(s.nustatytiEgzamina(11));
}

TEST_CASE("nustatytiPazymius - netinkamas pazymys vektoriuje") {
    Studentas s("A", "B", {5}, 5);
    CHECK_THROWS(s.nustatytiPazymius({5, 11}));
}

// ---------------------------------------------------------------------------
// arVargsiukas
// ---------------------------------------------------------------------------

TEST_CASE("arVargsiukas pagal vidurki - vargsiukas") {
    // galutinis vid = 0.4*1 + 0.6*1 = 1.0 < 5
    Studentas s("A", "B", {1}, 1);
    CHECK(s.arVargsiukas(false));
}

TEST_CASE("arVargsiukas pagal vidurki - kietiakas") {
    // galutinis vid = 0.4*10 + 0.6*10 = 10.0 >= 5
    Studentas s("A", "B", {10}, 10);
    CHECK_FALSE(s.arVargsiukas(false));
}

TEST_CASE("arVargsiukas pagal mediana - vargsiukas") {
    Studentas s("A", "B", {1}, 1);
    CHECK(s.arVargsiukas(true));
}

TEST_CASE("arVargsiukas pagal mediana - kietiakas") {
    Studentas s("A", "B", {10}, 10);
    CHECK_FALSE(s.arVargsiukas(true));
}

TEST_CASE("arVargsiukas - riba ties 5.0") {
    // galutinis = 0.4*5 + 0.6*5 = 5.0, riba yra < 5, tai kietiakas
    Studentas s("A", "B", {5}, 5);
    CHECK_FALSE(s.arVargsiukas(false));
    CHECK_FALSE(s.arVargsiukas(true));
}
