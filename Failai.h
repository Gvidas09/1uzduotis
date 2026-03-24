#pragma once
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <exception>

#include "Studentas.h"

bool nuskaityti_studenta_is_eilutes(const std::string& eilute, Studentas& a, bool& praleisti);
bool generuoti_studentu_faila(const std::string& failas, int kiek_studentu, int kiek_nd);
void sudaryti_rezultatu_failu_vardus(const std::string& pradinis_failas, std::string& vargsiuku_failas, std::string& kietiaku_failas);

template <typename Container>
bool nuskaityti_is_failo(const std::string& failas, Container& grupe, int& praleista) {
    grupe.clear();
    praleista = 0;

    try {
        std::ifstream in;
        in.exceptions(std::ios::badbit);
        in.open(failas);

        if (!in.is_open()) {
            std::cout << "Klaida: failas neegzistuoja arba nepavyko jo atidaryti: " << failas << "\n";
            return false;
        }

        std::string line;
        while (std::getline(in, line)) {
            if (line.empty()) continue;

            Studentas a;
            bool atmesti = false;
            if (!nuskaityti_studenta_is_eilutes(line, a, atmesti)) {
                if (atmesti) praleista++;
                continue;
            }

            grupe.push_back(a);
        }

        if (in.bad()) {
            std::cout << "Klaida: ivyko skaitymo klaida (badbit) skaitant faila: " << failas << "\n";
            grupe.clear();
            praleista = 0;
            return false;
        }

        return true;
    }
    catch (const std::ios_base::failure&) {
        std::cout << "Klaida: ivyko I/O klaida skaitant faila: " << failas << "\n";
        grupe.clear();
        praleista = 0;
        return false;
    }
    catch (const std::exception&) {
        std::cout << "Klaida: ivyko nenumatyta klaida skaitant faila.\n";
        grupe.clear();
        praleista = 0;
        return false;
    }
}

template <typename Container>
bool isvesti_i_faila(const Container& grupe, const std::string& failas) {
    try {
        std::ofstream out;
        out.exceptions(std::ios::failbit | std::ios::badbit);
        out.open(failas);

        out << std::left << std::setw(15) << "Vardas"
            << std::setw(20) << "Pavarde"
            << std::setw(18) << "Galutinis (Vid.)"
            << std::setw(18) << "Galutinis (Med.)"
            << "\n";

        out << std::string(15 + 20 + 18 + 18, '-') << "\n";

        out << std::fixed << std::setprecision(2);
        for (const auto& a : grupe) {
            out << std::left << std::setw(15) << a.vardas
                << std::setw(20) << a.pavarde
                << std::setw(18) << a.gal_vid
                << std::setw(18) << a.gal_med
                << "\n";
        }

        return true;
    }
    catch (const std::ios_base::failure&) {
        std::cout << "Klaida: nepavyko sukurti arba irasyti i faila: " << failas << "\n";
        return false;
    }
    catch (const std::exception&) {
        std::cout << "Klaida: ivyko nenumatyta klaida rasant i faila.\n";
        return false;
    }
}

inline void padalinti_studentus(const std::vector<Studentas>& visi, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietiakiai) {
    vargsiukai.clear();
    kietiakiai.clear();

    for (const auto& s : visi) {
        if (s.gal_vid < 5.0) {
            vargsiukai.push_back(s);
        } else {
            kietiakiai.push_back(s);
        }
    }
}