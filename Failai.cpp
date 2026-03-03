#include <iostream>
#include "Failai.h"
#include <fstream>
#include <sstream>
#include <iomanip>

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

bool nuskaityti_is_failo(const string &failas, vector<Studentas> &grupe, int &praleista) {
    ifstream in(failas);
    if (!in) {
        std::cout << "Nepavyko atidaryti failo: " << failas << endl;
        return false;
    }

    grupe.clear();
    praleista = 0;

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

    return true;
}

void isvesti_i_faila(const vector<Studentas> &grupe, const string &failas) {
    ofstream out(failas);
    if (!out) {
        std::cout << "Nepavyko sukurti failo.\n";
        return;
    }

    out << left << setw(15) << "Vardas"
        << setw(20) << "Pavarde"
        << setw(18) << "Galutinis (Vid.)"
        << setw(18) << "Galutinis (Med.)"
        << "\n";

    out << string(15 + 20 + 18 + 18, '-') << "\n";

    out << fixed << setprecision(2);
    for (const auto &a : grupe) {
        out << left << setw(15) << a.vardas
            << setw(20) << a.pavarde
            << setw(18) << a.gal_vid
            << setw(18) << a.gal_med
            << "\n";
    }
}