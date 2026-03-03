#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <chrono>

#include "Studentas.h"
#include "Ivedimas.h"
#include "Failai.h"
#include "Rikiavimas.h"

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;
using std::endl;
using std::numeric_limits;
using std::streamsize;

using std::chrono::high_resolution_clock;
using std::chrono::duration;

int atsitiktinis_pazymys() {
    return rand() % 10 + 1;
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