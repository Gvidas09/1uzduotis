#include "Testai.h"
#include "Studentas.h"
#include <iostream>
#include <sstream>

namespace {

void spausdinti_rezultata(const std::string& testo_pavadinimas, bool pavyko) {
    std::cout << (pavyko ? "[OK] " : "[NEPAVYKO] ") << testo_pavadinimas << "\n";
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
    return in.good() &&
           s.vardas() == "Jonas" &&
           s.pavarde() == "Jonaitis" &&
           s.pazymiai().size() == 3 &&
           s.egzaminas() == 9;
}

bool testuoti_ivedimo_operatoriu_su_blogais_duomenimis() {
    std::istringstream in("Jonas Jonaitis 8 11 9\n");
    Studentas s;
    in >> s;
    return in.fail();
}

} // namespace

void vykdyti_v12_testus() {
    std::cout << "\nV1.2 TESTAI - ivesties ir isvesties operatoriai\n\n";

    spausdinti_rezultata("Isvesties operatorius <<", testuoti_isvesties_operatoriu());
    spausdinti_rezultata("Ivesties operatorius >> is failo formato", testuoti_ivedimo_operatoriu_is_failo_formato());
    spausdinti_rezultata("Ivesties operatorius >> su blogais duomenimis", testuoti_ivedimo_operatoriu_su_blogais_duomenimis());

    std::cout << "\nPradiniai v1.2 testai baigti.\n";
}