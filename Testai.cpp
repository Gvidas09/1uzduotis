#include "Testai.h"
#include "Studentas.h"
#include "Zmogus.h"
#include <iostream>
#include <sstream>
#include <type_traits>
#include <utility>

namespace {

void spausdinti_rezultata(const std::string& testo_pavadinimas, bool pavyko) {
    std::cout << (pavyko ? "[OK] " : "[NEPAVYKO] ") << testo_pavadinimas << "\n";
}

bool testuoti_ar_zmogus_abstraktus() {
    return std::is_abstract<Zmogus>::value;
}

bool testuoti_paveldeta_zmogaus_dali() {
    Studentas s("Jonas", "Jonaitis", {8, 9, 10}, 9);
    Zmogus* zmogus = &s;

    return zmogus->vardas() == "Jonas" && zmogus->pavarde() == "Jonaitis";
}

bool testuoti_numatytaji_konstruktoriu() {
    Studentas s;
    return s.vardas().empty() && s.pavarde().empty() && s.pazymiai().empty() &&
           s.egzaminas() == 0 && s.galutinisVid() == 0.0 && s.galutinisMed() == 0.0;
}

bool testuoti_parametru_konstruktoriu() {
    Studentas s("Jonas", "Jonaitis", {8, 9, 10}, 9);
    return s.vardas() == "Jonas" && s.pavarde() == "Jonaitis" &&
           s.egzaminas() == 9 && !s.pazymiai().empty();
}

bool testuoti_kopijavimo_konstruktoriu() {
    Studentas a("Ona", "Onaite", {7, 8, 9}, 10);
    Studentas b(a);
    return b.vardas() == a.vardas() && b.pavarde() == a.pavarde() &&
           b.pazymiai() == a.pazymiai() && b.egzaminas() == a.egzaminas();
}

bool testuoti_perkelimo_konstruktoriu() {
    Studentas a("Petras", "Petraitis", {6, 7, 8}, 9);
    Studentas b(std::move(a));
    return b.vardas() == "Petras" && b.pavarde() == "Petraitis" &&
           a.vardas().empty() && a.pavarde().empty() && a.pazymiai().empty();
}

bool testuoti_kopijavimo_priskyrima() {
    Studentas a("Ieva", "Ievaite", {10, 9, 8}, 9);
    Studentas b;
    b = a;
    return b.vardas() == a.vardas() && b.pavarde() == a.pavarde() &&
           b.pazymiai() == a.pazymiai() && b.egzaminas() == a.egzaminas();
}

bool testuoti_perkelimo_priskyrima() {
    Studentas a("Matas", "Matutis", {5, 6, 7}, 8);
    Studentas b;
    b = std::move(a);
    return b.vardas() == "Matas" && b.pavarde() == "Matutis" &&
           a.vardas().empty() && a.pavarde().empty() && a.pazymiai().empty();
}

bool testuoti_destruktoriu() {
    try {
        Studentas* s = new Studentas("Tomas", "Tomaitis", {8, 9, 10}, 9);
        delete s;
        return true;
    }
    catch (...) {
        return false;
    }
}

bool testuoti_isvesties_operatoriu() {
    Studentas s("Aiste", "Aistaite", {10, 9, 8}, 10);
    std::ostringstream out;
    out << s;
    std::string tekstas = out.str();
    return tekstas.find("Aiste") != std::string::npos &&
           tekstas.find("Aistaite") != std::string::npos;
}

bool testuoti_ivedimo_operatoriu_is_failo_formato() {
    std::istringstream in("Jonas Jonaitis 8 9 10 9\n");
    Studentas s;
    in >> s;
    return in.good() && s.vardas() == "Jonas" && s.pavarde() == "Jonaitis" &&
           s.pazymiai().size() == 3 && s.egzaminas() == 9;
}

bool testuoti_ivedimo_operatoriu_su_blogais_duomenimis() {
    std::istringstream in("Jonas Jonaitis 8 11 9\n");
    Studentas s;
    in >> s;
    return in.fail();
}

} // namespace

void vykdyti_v15_testus() {
    std::cout << "\nV1.5 TESTAI - paveldimumas, abstrakti klase ir v1.2 funkcionalumas\n\n";

    spausdinti_rezultata("Zmogus klase yra abstrakti", testuoti_ar_zmogus_abstraktus());
    spausdinti_rezultata("Studentas paveldi Zmogus duomenis", testuoti_paveldeta_zmogaus_dali());
    spausdinti_rezultata("Numatytasis konstruktorius", testuoti_numatytaji_konstruktoriu());
    spausdinti_rezultata("Konstruktorius su parametrais", testuoti_parametru_konstruktoriu());
    spausdinti_rezultata("Kopijavimo konstruktorius", testuoti_kopijavimo_konstruktoriu());
    spausdinti_rezultata("Perkelimo konstruktorius", testuoti_perkelimo_konstruktoriu());
    spausdinti_rezultata("Kopijavimo priskyrimo operatorius", testuoti_kopijavimo_priskyrima());
    spausdinti_rezultata("Perkelimo priskyrimo operatorius", testuoti_perkelimo_priskyrima());
    spausdinti_rezultata("Destruktorius", testuoti_destruktoriu());
    spausdinti_rezultata("Isvesties operatorius <<", testuoti_isvesties_operatoriu());
    spausdinti_rezultata("Ivesties operatorius >> is failo formato", testuoti_ivedimo_operatoriu_is_failo_formato());
    spausdinti_rezultata("Ivesties operatorius >> su blogais duomenimis", testuoti_ivedimo_operatoriu_su_blogais_duomenimis());

    std::cout << "\nV1.5 testai baigti.\n";
}