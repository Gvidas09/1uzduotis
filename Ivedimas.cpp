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
        throw std::runtime_error("Ivesties klaida: tiketasi sveiko skaiciaus.");
    }
    return x;
}

int ivesti_skaiciu(const string& tekstas, int nuo, int iki) {
    while (true) {
        try {
            cout << tekstas;
            int x = skaityti_int();
            if (x < nuo || x > iki) throw std::out_of_range("Reiksme uz ribu.");
            return x;
        } catch (const std::exception&) {
            cout << "Klaida: iveskite skaiciu nuo " << nuo << " iki " << iki << ".\n";
        }
    }
}

int ivesti_kieki(const string& tekstas) {
    while (true) {
        try {
            cout << tekstas;
            int x = skaityti_int();
            if (x <= 0) throw std::out_of_range("Kiekis turi buti > 0.");
            return x;
        } catch (const std::exception&) {
            cout << "Klaida: skaicius turi buti bent 1.\n";
        }
    }
}

int meniu() {
    cout << "\nMeniu:\n";
    cout << "1 - Ivesti ranka\n";
    cout << "2 - Generuoti tik pazymius (vardas/pavarde ranka)\n";
    cout << "3 - Generuoti varda, pavarde ir pazymius\n";
    cout << "4 - Baigti\n";
    cout << "5 - Nuskaityti studentus is failo (v0.2)\n";
    cout << "6 - Rikiuoti ir isvesti rezultatus\n";
    return ivesti_skaiciu("Pasirinkimas: ", 1, 6);
}