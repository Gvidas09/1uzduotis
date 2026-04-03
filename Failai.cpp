#include "Failai.h"
#include <sstream>
#include <random>
#include <utility>

namespace {
std::mt19937& generatorius() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}

int atsitiktinis_pazymys() {
    static std::uniform_int_distribution<int> dist(1, 10);
    return dist(generatorius());
}
}

bool nuskaityti_studenta_is_eilutes(const std::string& eilute, Studentas& a, bool& praleisti) {
    praleisti = false;

    std::istringstream iss(eilute);

    std::string vardas;
    std::string pavarde;
    if (!(iss >> vardas >> pavarde)) {
        praleisti = true;
        return false;
    }

    if (vardas == "Vardas" && pavarde == "Pavarde") {
        return false;
    }

    std::vector<int> skaiciai;
    skaiciai.reserve(16);

    int x = 0;
    while (iss >> x) {
        skaiciai.push_back(x);
    }

    if (!iss.eof()) {
        praleisti = true;
        return false;
    }

    if (skaiciai.size() < 2) {
        praleisti = true;
        return false;
    }

    for (int v : skaiciai) {
        if (v < 1 || v > 10) {
            praleisti = true;
            return false;
        }
    }

    int egz = skaiciai.back();
    skaiciai.pop_back();

    a = Studentas(vardas, pavarde, skaiciai, egz);
    return true;
}

bool generuoti_studentu_faila(const std::string& failas, int kiek_studentu, int kiek_nd) {
    try {
        std::ofstream out;
        out.exceptions(std::ios::failbit | std::ios::badbit);
        out.open(failas);

        out << "Vardas Pavarde ";
        for (int i = 1; i <= kiek_nd; i++) {
            out << "ND" << i << ' ';
        }
        out << "Egz.\n";

        for (int i = 1; i <= kiek_studentu; i++) {
            out << "Vardas" << i << ' '
                << "Pavarde" << i << ' ';

            for (int j = 0; j < kiek_nd; j++) {
                out << atsitiktinis_pazymys() << ' ';
            }

            out << atsitiktinis_pazymys() << '\n';
        }

        return true;
    }
    catch (const std::ios_base::failure&) {
        std::cout << "Klaida: nepavyko sugeneruoti failo: " << failas << "\n";
        return false;
    }
    catch (const std::exception&) {
        std::cout << "Klaida: ivyko nenumatyta klaida generuojant faila.\n";
        return false;
    }
}

void sudaryti_rezultatu_failu_vardus(const std::string& pradinis_failas, const std::string& konteinerio_vardas, int strategija, std::string& vargsiuku_failas, std::string& kietiaku_failas) {
    std::size_t taskas = pradinis_failas.rfind('.');
    std::string priedas = "_" + konteinerio_vardas + "_s" + std::to_string(strategija);

    if (taskas == std::string::npos) {
        vargsiuku_failas = pradinis_failas + priedas + "_vargsiukai.txt";
        kietiaku_failas = pradinis_failas + priedas + "_kietiakiai.txt";
    } else {
        std::string pagrindas = pradinis_failas.substr(0, taskas);
        std::string galune = pradinis_failas.substr(taskas);

        vargsiuku_failas = pagrindas + priedas + "_vargsiukai" + galune;
        kietiaku_failas = pagrindas + priedas + "_kietiakiai" + galune;
    }
}