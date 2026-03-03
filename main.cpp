#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <limits>
#include <chrono>
#include "Studentas.h"
#include "Ivedimas.h"
#include "Failai.h"


using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;
using std::endl;
using std::sort;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::getline;
using std::numeric_limits;
using std::streamsize;
using std::ws;

using std::chrono::high_resolution_clock;
using std::chrono::duration;


int atsitiktinis_pazymys() {
    return rand() % 10 + 1;
}

bool ar_skaitmuo(char c) {
    return c >= '0' && c <= '9';
}

int skaicius_gale(const string &s) {
    int i = (int)s.size() - 1;
    if (i < 0) return -1;
    if (!ar_skaitmuo(s[i])) return -1;

    int daugiklis = 1;
    int sk = 0;

    while (i >= 0 && ar_skaitmuo(s[i])) {
        sk += (s[i] - '0') * daugiklis;
        daugiklis *= 10;
        i--;
    }
    return sk;
}

string tekstas_be_galo_skaiciaus(const string &s) {
    int i = (int)s.size() - 1;
    if (i < 0) return s;
    if (!ar_skaitmuo(s[i])) return s;

    while (i >= 0 && ar_skaitmuo(s[i])) i--;
    return s.substr(0, i + 1);
}

bool palyginti_nat(const string &a, const string &b) {
    string ta = tekstas_be_galo_skaiciaus(a);
    string tb = tekstas_be_galo_skaiciaus(b);

    if (ta != tb) return ta < tb;

    int na = skaicius_gale(a);
    int nb = skaicius_gale(b);

    if (na != -1 && nb != -1) return na < nb;

    return a < b;
}

bool palyginti_pagal_varda(const Studentas &a, const Studentas &b) {
    if (a.vardas != b.vardas) return palyginti_nat(a.vardas, b.vardas);
    return palyginti_nat(a.pavarde, b.pavarde);
}

bool palyginti_pagal_pavarde(const Studentas &a, const Studentas &b) {
    if (a.pavarde != b.pavarde) return palyginti_nat(a.pavarde, b.pavarde);
    return palyginti_nat(a.vardas, b.vardas);
}

bool palyginti_pagal_vidurki(const Studentas &a, const Studentas &b) {
    if (a.gal_vid != b.gal_vid) return a.gal_vid < b.gal_vid;
    if (a.pavarde != b.pavarde) return palyginti_nat(a.pavarde, b.pavarde);
    return palyginti_nat(a.vardas, b.vardas);
}

bool palyginti_pagal_mediana(const Studentas &a, const Studentas &b) {
    if (a.gal_med != b.gal_med) return a.gal_med < b.gal_med;
    if (a.pavarde != b.pavarde) return palyginti_nat(a.pavarde, b.pavarde);
    return palyginti_nat(a.vardas, b.vardas);
}


void rikiuoti(vector<Studentas> &grupe) {
    if (grupe.empty()) {
        cout << "Grupe tuscia - nera ka rikiuoti.\n";
        return;
    }

    cout << "\nRikiuoti studentus pagal:\n";
    cout << "1 - Varda\n";
    cout << "2 - Pavarde\n";
    cout << "3 - Galutini (Vid.)\n";
    cout << "4 - Galutini (Med.)\n";

    int r = ivesti_skaiciu("Pasirinkimas: ", 1, 4);

    if (r == 1) sort(grupe.begin(), grupe.end(), palyginti_pagal_varda);
    else if (r == 2) sort(grupe.begin(), grupe.end(), palyginti_pagal_pavarde);
    else if (r == 3) sort(grupe.begin(), grupe.end(), palyginti_pagal_vidurki);
    else sort(grupe.begin(), grupe.end(), palyginti_pagal_mediana);
}

void isvesti_i_ekrana(const vector<Studentas> &grupe) {
    cout << left << setw(15) << "Vardas"
         << setw(20) << "Pavarde"
         << setw(18) << "Galutinis (Vid.)"
         << setw(18) << "Galutinis (Med.)"
         << "\n";

    cout << string(15 + 20 + 18 + 18, '-') << "\n";

    cout << fixed << setprecision(2);
    for (const auto &a : grupe) {
        cout << left << setw(15) << a.vardas
             << setw(20) << a.pavarde
             << setw(18) << a.gal_vid
             << setw(18) << a.gal_med
             << "\n";
    }
}

void isvedimo_pasirinkimas(const vector<Studentas> &grupe) {
    if (grupe.empty()) {
        cout << "Grupe tuscia.\n";
        return;
    }

    cout << "\nKur isvesti rezultatus?\n";
    cout << "1 - I ekrana\n";
    cout << "2 - I faila\n";
    int kur = ivesti_skaiciu("Pasirinkimas: ", 1, 2);

    if (kur == 1) {
        if (grupe.size() > 10000) {
            cout << "Perspejimas: studentu labai daug, isvedimas i ekrana gali buti labai letas.\n";
            cout << "1 - Vis tiek testi\n";
            cout << "2 - Geriau i faila\n";
            int k = ivesti_skaiciu("Pasirinkimas: ", 1, 2);
            if (k == 2) {
                string outname;
                cout << "Failo pavadinimas (pvz. rezultatai.txt): ";
                cin >> outname;
                isvesti_i_faila(grupe, outname);
                cout << "Rezultatai irasyti i faila: " << outname << endl;
                return;
            }
        }
        isvesti_i_ekrana(grupe);
    } else {
        string outname;
        cout << "Failo pavadinimas (pvz. rezultatai.txt): ";
        cin >> outname;
        isvesti_i_faila(grupe, outname);
        cout << "Rezultatai irasyti i faila: " << outname << endl;
    }
}

int main() {
    srand((unsigned)time(NULL));

    Studentas a;
    vector<Studentas> grupe;

    while (true) {
        int p = meniu();
        if (p == 4) break;

        if (p == 1) {
            a.paz.clear();

            cout << "Iveskite varda ir pavarde: ";
            cin >> a.vardas >> a.pavarde;

            cout << "Iveskite namu darbu pazymius (1-10), 0 - baigti:\n";
            int temp;

            while (true) {
                cout << "Pazymys: ";
                cin >> temp;

                while (!cin) {
                    cout << "Klaida: iveskite skaiciu: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> temp;
                }

                if (temp == 0) break;

                if (temp < 1 || temp > 10) {
                    cout << "Klaida: pazymys turi buti 1-10.\n";
                    continue;
                }

                a.paz.push_back(temp);
            }

            a.egz = ivesti_skaiciu("Egzamino pazymys (1-10): ", 1, 10);

            skaiciuoti(a);
            grupe.push_back(a);

            cout << "Prideta. Is viso studentu: " << grupe.size() << endl;
        }
        else if (p == 2) {
            a.paz.clear();

            cout << "Iveskite varda ir pavarde: ";
            cin >> a.vardas >> a.pavarde;

            int kiek = ivesti_kieki("Kiek ND generuoti? ");
            for (int i = 0; i < kiek; i++) a.paz.push_back(atsitiktinis_pazymys());

            a.egz = atsitiktinis_pazymys();

            skaiciuoti(a);
            grupe.push_back(a);

            cout << "Prideta. Is viso studentu: " << grupe.size() << endl;
        }
        else if (p == 3) {
            a.paz.clear();

            vector<string> vardai = {"Jonas","Ona","Ieva","Mantas","Egle","Tomas","Ruta","Paulius","Greta","Lukas"};
            vector<string> pavardes = {"Kazlauskas","Petrauskas","Jankauskas","Vaitkus","Zukauskas",
                                       "Stankevicius","Pocius","Noreika","Mikulenas","Sabonis"};

            a.vardas = vardai[rand() % (int)vardai.size()];
            a.pavarde = pavardes[rand() % (int)pavardes.size()];

            int kiek = ivesti_kieki("Kiek ND generuoti? ");
            for (int i = 0; i < kiek; i++) a.paz.push_back(atsitiktinis_pazymys());

            a.egz = atsitiktinis_pazymys();

            skaiciuoti(a);
            grupe.push_back(a);

            cout << "Prideta. Is viso studentu: " << grupe.size() << endl;
        }
        else if (p == 5) {
            cout << "Iveskite failo pavadinima: ";
            string fname;
            cin >> fname;

            int praleista = 0;

            auto start = high_resolution_clock::now();
            bool ok = nuskaityti_is_failo(fname, grupe, praleista);
            auto end = high_resolution_clock::now();

            if (!ok) {
                cout << "Skaitymas nepavyko.\n";
            } else {
                duration<double> diff = end - start;
                cout << "Studentu: " << grupe.size() << endl;
                cout << "Laikas: " << diff.count() << " s\n";
                if (praleista > 0) cout << "Praleista eiluciu: " << praleista << endl;

                cout << "\nAr norite dabar rikiuoti ir isvesti?\n";
                cout << "1 - Taip\n";
                cout << "2 - Ne (grizti i meniu)\n";
                int ats = ivesti_skaiciu("Pasirinkimas: ", 1, 2);

                if (ats == 1) {
                    rikiuoti(grupe);
                    isvedimo_pasirinkimas(grupe);
                }
            }
        }
        else if (p == 6) {
            if (grupe.empty()) {
                cout << "Grupe tuscia.\n";
            } else {
                rikiuoti(grupe);
                isvedimo_pasirinkimas(grupe);
            }
        }
    }

    return 0;
}