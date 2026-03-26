#pragma once
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <exception>
#include <algorithm>
#include <iterator>

#include "Studentas.h"

bool nuskaityti_studenta_is_eilutes(const std::string& eilute, Studentas& a, bool& praleisti);
bool generuoti_studentu_faila(const std::string& failas, int kiek_studentu, int kiek_nd);

void sudaryti_rezultatu_failu_vardus(const std::string& pradinis_failas, std::string& vargsiuku_failas, std::string& kietiaku_failas);

void sudaryti_rezultatu_failu_vardus(const std::string& pradinis_failas, const std::string& konteinerio_vardas, int strategija, std::string& vargsiuku_failas, std::string& kietiaku_failas);

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

template <typename Container>
void rezervuoti_vieta(Container&, std::size_t) {}

inline void rezervuoti_vieta(std::vector<Studentas>& c, std::size_t n) { c.reserve(n); }
inline void rezervuoti_vieta(std::deque<Studentas>&, std::size_t) {}
inline void rezervuoti_vieta(std::list<Studentas>&, std::size_t) {}

template <typename Container>
void padalinti_studentus_1(const Container& visi, Container& vargsiukai, Container& kietiakiai, bool naudoti_mediana = false) {
    vargsiukai.clear();
    kietiakiai.clear();
    rezervuoti_vieta(vargsiukai, visi.size());
    rezervuoti_vieta(kietiakiai, visi.size());

    for (const auto& s : visi) {
        if (ar_vargsiukas(s, naudoti_mediana)) {
            vargsiukai.push_back(s);
        } else {
            kietiakiai.push_back(s);
        }
    }
}

template <typename Container>
void padalinti_studentus_2(Container& visi, Container& vargsiukai, Container& kietiakiai, bool naudoti_mediana = false) {
    vargsiukai.clear();
    kietiakiai.clear();
    rezervuoti_vieta(vargsiukai, visi.size());

    std::copy_if(visi.begin(), visi.end(), std::back_inserter(vargsiukai),
        [naudoti_mediana](const Studentas& s) { return ar_vargsiukas(s, naudoti_mediana); });

    visi.erase(std::remove_if(visi.begin(), visi.end(),
        [naudoti_mediana](const Studentas& s) { return ar_vargsiukas(s, naudoti_mediana); }),
        visi.end());

    kietiakiai = std::move(visi);
}

inline void padalinti_studentus_2(std::list<Studentas>& visi, std::list<Studentas>& vargsiukai, std::list<Studentas>& kietiakiai, bool naudoti_mediana = false) {
    vargsiukai.clear();
    kietiakiai.clear();

    for (auto it = visi.begin(); it != visi.end();) {
        if (ar_vargsiukas(*it, naudoti_mediana)) {
            auto perkelti = it++;
            vargsiukai.splice(vargsiukai.end(), visi, perkelti);
        } else {
            ++it;
        }
    }

    kietiakiai = std::move(visi);
}

template <typename Container>
void padalinti_studentus_3(Container& visi, Container& vargsiukai, Container& kietiakiai, bool naudoti_mediana = false) {
    vargsiukai.clear();
    kietiakiai.clear();

    auto riba = std::stable_partition(visi.begin(), visi.end(),
        [naudoti_mediana](const Studentas& s) { return ar_vargsiukas(s, naudoti_mediana); });

    rezervuoti_vieta(vargsiukai, (std::size_t)std::distance(visi.begin(), riba));
    rezervuoti_vieta(kietiakiai, (std::size_t)std::distance(riba, visi.end()));

    std::copy(visi.begin(), riba, std::back_inserter(vargsiukai));
    std::copy(riba, visi.end(), std::back_inserter(kietiakiai));
}

template <typename Container>
void padalinti_studentus(Container& visi, Container& vargsiukai, Container& kietiakiai, bool naudoti_mediana = false) {
    padalinti_studentus_1(visi, vargsiukai, kietiakiai, naudoti_mediana);
}

template <typename Container>
void padalinti_studentus(Container& visi, Container& vargsiukai, Container& kietiakiai, int strategija, bool naudoti_mediana = false) {
    if (strategija == 1) {
        padalinti_studentus_1(visi, vargsiukai, kietiakiai, naudoti_mediana);
    } else if (strategija == 2) {
        padalinti_studentus_2(visi, vargsiukai, kietiakiai, naudoti_mediana);
    } else {
        padalinti_studentus_3(visi, vargsiukai, kietiakiai, naudoti_mediana);
    }
}