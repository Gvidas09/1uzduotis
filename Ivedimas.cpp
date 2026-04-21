#include "Ivedimas.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <functional>

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

static int ivesti_su_tikrinimu(const string& tekstas, const std::function<bool(int)>& tinka, const string& klaidos_pranesimas) {
    while (true) {
        try {
            cout << tekstas;
            int x = skaityti_int();

            if (!tinka(x)) {
                throw std::out_of_range("Klaida: netinkama reiksme.");
            }

            return x;
        }
        catch (const std::runtime_error&) {
            cout << "Klaida: iveskite sveika skaiciu.\n";
        }
        catch (const std::out_of_range&) {
            cout << klaidos_pranesimas << "\n";
        }
    }
}

int ivesti_skaiciu(const string& tekstas, int nuo, int iki) {
    return ivesti_su_tikrinimu(
        tekstas,
        [nuo, iki](int x) { return x >= nuo && x <= iki; },
        "Klaida: iveskite skaiciu nuo " + std::to_string(nuo) + " iki " + std::to_string(iki) + "."
    );
}

int ivesti_kieki(const string& tekstas) {
    return ivesti_su_tikrinimu(
        tekstas,
        [](int x) { return x > 0; },
        "Klaida: skaicius turi buti bent 1."
    );
}

int meniu() {
    cout << "\nMeniu:\n";
    cout << "1 - Generuoti penkis testinius failus\n";
    cout << "2 - Apdoroti viena faila\n";
    cout << "3 - Vykdyti spartos tyrima visiems sugeneruotiems failams\n";
    cout << "4 - Vykdyti v1.1 fiksuota tyrima README lentelems\n";
    cout << "5 - Vykdyti v1.2 testus\n";
    cout << "6 - Baigti\n";
    return ivesti_skaiciu("Pasirinkimas: ", 1, 6);
}

int pasirinkti_rikiavimo_kriteriju() {
    cout << "\nRikiuoti studentus pagal:\n";
    cout << "1 - Varda\n";
    cout << "2 - Pavarde\n";
    cout << "3 - Galutini (Vid.)\n";
    cout << "4 - Galutini (Med.)\n";
    return ivesti_skaiciu("Pasirinkimas: ", 1, 4);
}

int pasirinkti_konteineri(bool leisti_visus) {
    cout << "\nNaudoti konteineri:\n";
    cout << "1 - std::vector\n";
    cout << "2 - std::list\n";
    cout << "3 - std::deque\n";
    if (leisti_visus) {
        cout << "4 - Visus tris konteinerius\n";
        return ivesti_skaiciu("Pasirinkimas: ", 1, 4);
    }
    return ivesti_skaiciu("Pasirinkimas: ", 1, 3);
}

int pasirinkti_strategija(bool leisti_visas) {
    cout << "\nNaudoti studentu dalijimo strategija:\n";
    cout << "1 - Du nauji konteineriai (vargsiukai ir kietiakiai)\n";
    cout << "2 - Vienas naujas konteineris vargsiukams, kiti lieka pradiniame\n";
    cout << "3 - Skaidymas naudojant stable_partition principa\n";
    if (leisti_visas) {
        cout << "4 - Visas tris strategijas\n";
        return ivesti_skaiciu("Pasirinkimas: ", 1, 4);
    }
    return ivesti_su_tikrinimu("Pasirinkimas: ",
                               [](int x) { return x >= 1 && x <= 3; },
                               "Klaida: iveskite skaiciu nuo 1 iki 3.");
}