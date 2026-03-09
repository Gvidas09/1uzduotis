#include <iostream>
#include "Failai.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <exception>

using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::string;
using std::vector;
using std::getline;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;
using std::endl;

bool nuskaityti_is_failo(const string& failas, vector<Studentas>& grupe, int& praleista) {
    grupe.clear();
    praleista = 0;

    try {
        ifstream in;
        in.exceptions(std::ios::badbit);
        in.open(failas);

        if (!in.is_open()) {
            std::cout << "Klaida: failas neegzistuoja arba nepavyko jo atidaryti: " << failas << endl;
            return false;
        }

        string line;
        while (getline(in, line)) {
            if (line.empty()) continue;

            istringstream iss(line);

            Studentas a;
            if (!(iss >> a.vardas >> a.pavarde)) {
                praleista++;
                continue;
            }

            if (a.vardas == "Vardas" && a.pavarde == "Pavarde") continue;

            vector<int> skaiciai;
            int x;
            while (iss >> x) skaiciai.push_back(x);

            if (!iss.eof()) {
                praleista++;
                continue;
            }

            if (skaiciai.size() < 2) {
                praleista++;
                continue;
            }

            bool bloga = false;
            for (int v : skaiciai) {
                if (v < 1 || v > 10) {
                    bloga = true;
                    break;
                }
            }

            if (bloga) {
                praleista++;
                continue;
            }

            a.egz = skaiciai.back();
            skaiciai.pop_back();
            a.paz = skaiciai;

            skaiciuoti(a);
            grupe.push_back(a);
        }

        if (in.bad()) {
            std::cout << "Klaida: ivyko skaitymo klaida (badbit) skaitant faila: " << failas << endl;
            grupe.clear();
            praleista = 0;
            return false;
        }

        return true;
    }
    catch (const std::ios_base::failure&) {
        std::cout << "Klaida: ivyko I/O klaida skaitant faila: " << failas << endl;
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

void isvesti_i_faila(const vector<Studentas>& grupe, const string& failas) {
    try {
        ofstream out;
        out.exceptions(std::ios::failbit | std::ios::badbit);
        out.open(failas);

        out << left << setw(15) << "Vardas"
            << setw(20) << "Pavarde"
            << setw(18) << "Galutinis (Vid.)"
            << setw(18) << "Galutinis (Med.)"
            << "\n";

        out << string(15 + 20 + 18 + 18, '-') << "\n";

        out << fixed << setprecision(2);
        for (const auto& a : grupe) {
            out << left << setw(15) << a.vardas
                << setw(20) << a.pavarde
                << setw(18) << a.gal_vid
                << setw(18) << a.gal_med
                << "\n";
        }
    }
    catch (const std::ios_base::failure&) {
        std::cout << "Klaida: nepavyko sukurti arba irasyti i faila: " << failas << endl;
    }
    catch (const std::exception&) {
        std::cout << "Klaida: ivyko nenumatyta klaida rasant i faila.\n";
    }
}

bool generuoti_studentu_faila(const string& failas, int kiek_studentu, int kiek_nd) {
    try {
        ofstream out;
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
                out << (rand() % 10 + 1) << ' ';
            }

            out << (rand() % 10 + 1) << '\n';
        }

        return true;
    }
    catch (const std::ios_base::failure&) {
        std::cout << "Klaida: nepavyko sugeneruoti failo: " << failas << endl;
        return false;
    }
    catch (const std::exception&) {
        std::cout << "Klaida: ivyko nenumatyta klaida generuojant faila.\n";
        return false;
    }
}

void padalinti_studentus(const vector<Studentas>& visi,
                         vector<Studentas>& vargsiukai,
                         vector<Studentas>& kietiakiai) {
    vargsiukai.clear();
    kietiakiai.clear();

    vargsiukai.reserve(visi.size());
    kietiakiai.reserve(visi.size());

    for (const auto& s : visi) {
        if (s.gal_vid < 5.0) {
            vargsiukai.push_back(s);
        } else {
            kietiakiai.push_back(s);
        }
    }
}

void sudaryti_rezultatu_failu_vardus(const string& pradinis_failas,
                                     string& vargsiuku_failas,
                                     string& kietiaku_failas) {
    size_t taskas = pradinis_failas.rfind('.');

    if (taskas == string::npos) {
        vargsiuku_failas = pradinis_failas + "_vargsiukai.txt";
        kietiaku_failas = pradinis_failas + "_kietiakiai.txt";
    } else {
        string pagrindas = pradinis_failas.substr(0, taskas);
        string galune = pradinis_failas.substr(taskas);

        vargsiuku_failas = pagrindas + "_vargsiukai" + galune;
        kietiaku_failas = pagrindas + "_kietiakiai" + galune;
    }
}