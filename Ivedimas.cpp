#include "Ivedimas.h"
#include <iostream>
#include <limits>
#include <stdexcept>

using std::cin;
using std::cout;
using std::string;
using std::numeric_limits;
using std::streamsize;

static int skaityti_int() {
    int x;
    if (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw std::runtime_error("Klaida: tiketasi sveiko skaiciaus.");
    }
    return x;
}

int ivesti_skaiciu(const string& tekstas, int nuo, int iki) {
    while (true) {
        try {
            cout << tekstas;
            int x = skaityti_int();

            if (x < nuo || x > iki) {
                throw std::out_of_range("Klaida: reiksme uz ribu.");
            }

            return x;
        } catch (const std::runtime_error&) {
            cout << "Klaida: iveskite sveika skaiciu.\n";
        } catch (const std::out_of_range&) {
            cout << "Klaida: iveskite skaiciu nuo " << nuo << " iki " << iki << ".\n";
        }
    }
}

int ivesti_kieki(const string& tekstas) {
    while (true) {
        try {
            cout << tekstas;
            int x = skaityti_int();

            if (x <= 0) {
                throw std::out_of_range("Klaida: kiekis netinkamas.");
            }

            return x;
        } catch (const std::runtime_error&) {
            cout << "Klaida: iveskite sveika skaiciu.\n";
        } catch (const std::out_of_range&) {
            cout << "Klaida: skaicius turi buti bent 1.\n";
        }
    }
}

int meniu() {
    cout << "\nMeniu:\n";
    cout << "1 - Generuoti penkis testinius failus\n";
    cout << "2 - Apdoroti viena faila\n";
    cout << "3 - Vykdyti spartos tyrima visiems sugeneruotiems failams\n";
    cout << "4 - Baigti\n";
    return ivesti_skaiciu("Pasirinkimas: ", 1, 4);
}

int pasirinkti_rikiavimo_kriteriju() {
    cout << "\nRikiuoti studentus pagal:\n";
    cout << "1 - Varda\n";
    cout << "2 - Pavarde\n";
    cout << "3 - Galutini (Vid.)\n";
    cout << "4 - Galutini (Med.)\n";
    return ivesti_skaiciu("Pasirinkimas: ", 1, 4);
}