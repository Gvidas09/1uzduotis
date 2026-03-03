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

bool nuskaityti_is_failo(const string &failas, vector<Studentas> &grupe, int &praleista) {
    grupe.clear();
    praleista = 0;

    try {
        ifstream in;

        // SVARBIAUSIA: nemetam isimtis ant failbit, nes getline() EOF metu uzdeda failbit.
        // Paliekam tik badbit (rimtos I/O klaidos: disko/stream'o klaidos).
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

            // praleidziam antrastine eilute
            if (a.vardas == "Vardas" && a.pavarde == "Pavarde") continue;

            vector<int> skaiciai;
            int x;
            while (iss >> x) skaiciai.push_back(x);

            // jei liko ne skaiciai (pvz. raide), laikom eilute bloga
            if (!iss.eof()) {
                praleista++;
                continue;
            }

            // turi buti bent 1 ND + egzaminas (t.y. bent 2 skaiciai)
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

        // jei norisi, galima patikrinti ar ne ivyko rimta skaitymo klaida
        if (in.bad()) {
            std::cout << "Klaida: ivyko skaitymo klaida (badbit) skaitant faila: " << failas << endl;
            grupe.clear();
            praleista = 0;
            return false;
        }

        return true;
    }
    catch (const std::ios_base::failure &) {
        std::cout << "Klaida: ivyko I/O klaida skaitant faila: " << failas << endl;
        grupe.clear();
        praleista = 0;
        return false;
    }
    catch (const std::exception &) {
        std::cout << "Klaida: ivyko nenumatyta klaida skaitant faila.\n";
        grupe.clear();
        praleista = 0;
        return false;
    }
}

void isvesti_i_faila(const vector<Studentas> &grupe, const string &failas) {
    try {
        ofstream out;

        // Rasymui failbit tinka (pvz. nepavyko irasyti), todel paliekam kaip buvo.
        out.exceptions(std::ios::failbit | std::ios::badbit);

        out.open(failas);

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
    catch (const std::ios_base::failure &) {
        std::cout << "Klaida: nepavyko sukurti arba irasyti i faila: " << failas << endl;
    }
    catch (const std::exception &) {
        std::cout << "Klaida: ivyko nenumatyta klaida rasant i faila.\n";
    }
}