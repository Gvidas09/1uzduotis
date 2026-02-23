#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <fstream>

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
using std::numeric_limits;
using std::streamsize;
using std::ofstream;

struct Studentas {
    string Vardas;
    string Pavarde;
    vector<int> paz;
    int exam = 0;

    double rezVid = 0.0;
    double rezMed = 0.0;
};

double mediana(const vector<int> &paz) {
    if (paz.empty()) return 0.0;

    vector<int> tmp = paz;
    sort(tmp.begin(), tmp.end());

    int n = (int)tmp.size();
    if (n % 2 == 1) return (double)tmp[n / 2];
    return (tmp[n / 2 - 1] + tmp[n / 2]) / 2.0;
}

int atsitiktinisPazymys() { return rand() % 10 + 1; }

int ivestiSkaiciu(const string &tekstas, int nuo, int iki) {
    int x;
    cout << tekstas;
    cin >> x;

    while (!cin || x < nuo || x > iki) {
        cout << "Klaida: iveskite skaiciu nuo " << nuo << " iki " << iki << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> x;
    }
    return x;
}

int ivestiKieki(const string &tekstas) {
    int x;
    cout << tekstas;
    cin >> x;

    while (!cin || x <= 0) {
        cout << "Klaida: skaicius turi buti bent 1. Iveskite dar karta: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> x;
    }
    return x;
}

int meniu() {
    int x;
    cout << "\nMeniu:\n";
    cout << "1 - Ivesti ranka\n";
    cout << "2 - Generuoti tik pazymius (vardas/pavarde ranka)\n";
    cout << "3 - Generuoti varda, pavarde ir pazymius\n";
    cout << "4 - Baigti\n";
    cout << "5 - Rikiuoti ir isvesti rezultatus\n";
    cout << "Pasirinkimas: ";
    cin >> x;

    while (!cin || x < 1 || x > 5) {
        cout << "Klaida: iveskite skaiciu nuo 1 iki 5: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> x;
    }
    return x;
}

void skaiciuoti(Studentas &A) {
    double vid = 0.0;
    if (!A.paz.empty()) {
        long long sum = 0;
        for (int x : A.paz) sum += x;
        vid = (double)sum / (double)A.paz.size();
    }
    double med = mediana(A.paz);

    A.rezVid = vid * 0.4 + A.exam * 0.6;
    A.rezMed = med * 0.4 + A.exam * 0.6;
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

    int r = ivestiSkaiciu("Pasirinkimas: ", 1, 4);

    if (r == 1) {
        sort(grupe.begin(), grupe.end(),
             [](const Studentas &a, const Studentas &b) { return a.Vardas < b.Vardas; });
    } else if (r == 2) {
        sort(grupe.begin(), grupe.end(),
             [](const Studentas &a, const Studentas &b) { return a.Pavarde < b.Pavarde; });
    } else if (r == 3) {
        sort(grupe.begin(), grupe.end(),
             [](const Studentas &a, const Studentas &b) { return a.rezVid < b.rezVid; });
    } else {
        sort(grupe.begin(), grupe.end(),
             [](const Studentas &a, const Studentas &b) { return a.rezMed < b.rezMed; });
    }
}

void outputas(const vector<Studentas> &grupe) {
    cout << left << setw(15) << "Vardas"
         << setw(20) << "Pavarde"
         << setw(18) << "Galutinis (Vid.)"
         << setw(18) << "Galutinis (Med.)"
         << "\n";

    cout << string(15 + 20 + 18 + 18, '-') << "\n";

    cout << fixed << setprecision(2);
    for (const auto &A : grupe) {
        cout << left << setw(15) << A.Vardas
             << setw(20) << A.Pavarde
             << setw(18) << A.rezVid
             << setw(18) << A.rezMed
             << "\n";
    }
}

void outputasIFaila(const vector<Studentas> &grupe, const string &failas) {
    ofstream out(failas);
    if (!out) {
        cout << "Nepavyko sukurti failo.\n";
        return;
    }

    out << left << setw(15) << "Vardas"
        << setw(20) << "Pavarde"
        << setw(18) << "Galutinis (Vid.)"
        << setw(18) << "Galutinis (Med.)"
        << "\n";

    out << string(15 + 20 + 18 + 18, '-') << "\n";

    out << fixed << setprecision(2);
    for (const auto &A : grupe) {
        out << left << setw(15) << A.Vardas
            << setw(20) << A.Pavarde
            << setw(18) << A.rezVid
            << setw(18) << A.rezMed
            << "\n";
    }
}

void isvedimoPasirinkimas(const vector<Studentas> &grupe) {
    if (grupe.empty()) {
        cout << "Grupe tuscia.\n";
        return;
    }

    cout << "\nKur isvesti rezultatus?\n";
    cout << "1 - I ekrana\n";
    cout << "2 - I faila\n";
    int kur = ivestiSkaiciu("Pasirinkimas: ", 1, 2);

    if (kur == 1) {
        if (grupe.size() > 10000) {
            cout << "Perspejimas: studentu labai daug, isvedimas i ekrana gali buti labai letas.\n";
            cout << "1 - Vis tiek testi\n";
            cout << "2 - Geriau i faila\n";
            int k = ivestiSkaiciu("Pasirinkimas: ", 1, 2);
            if (k == 2) {
                string outname;
                cout << "Failo pavadinimas (pvz. rezultatai.txt): ";
                cin >> outname;
                outputasIFaila(grupe, outname);
                cout << "Rezultatai irasyti i faila: " << outname << endl;
                return;
            }
        }
        outputas(grupe);
    } else {
        string outname;
        cout << "Failo pavadinimas (pvz. rezultatai.txt): ";
        cin >> outname;
        outputasIFaila(grupe, outname);
        cout << "Rezultatai irasyti i faila: " << outname << endl;
    }
}

int main() {
    srand((unsigned)time(NULL));

    Studentas A;
    vector<Studentas> grupe;

    while (true) {
        int p = meniu();
        if (p == 4) break;

        if (p == 1) {
            A.paz.clear();

            cout << "Iveskite varda ir pavarde: ";
            cin >> A.Vardas >> A.Pavarde;

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

                A.paz.push_back(temp);
            }

            A.exam = ivestiSkaiciu("Egzamino pazymys (1-10): ", 1, 10);
            skaiciuoti(A);
            grupe.push_back(A);
            cout << "Prideta. Is viso studentu: " << grupe.size() << endl;
        }
        else if (p == 2) {
            A.paz.clear();

            cout << "Iveskite varda ir pavarde: ";
            cin >> A.Vardas >> A.Pavarde;

            int kiek = ivestiKieki("Kiek ND generuoti? ");
            for (int i = 0; i < kiek; i++) A.paz.push_back(atsitiktinisPazymys());

            A.exam = atsitiktinisPazymys();
            skaiciuoti(A);
            grupe.push_back(A);
            cout << "Prideta. Is viso studentu: " << grupe.size() << endl;
        }
        else if (p == 3) {
            A.paz.clear();

            vector<string> vardai = {"Jonas","Ona","Ieva","Mantas","Egle","Tomas","Ruta","Paulius","Greta","Lukas"};
            vector<string> pavardes = {"Kazlauskas","Petrauskas","Jankauskas","Vaitkus","Zukauskas",
                                       "Stankevicius","Pocius","Noreika","Mikulenas","Sabonis"};

            A.Vardas = vardai[rand() % (int)vardai.size()];
            A.Pavarde = pavardes[rand() % (int)pavardes.size()];

            int kiek = ivestiKieki("Kiek ND generuoti? ");
            for (int i = 0; i < kiek; i++) A.paz.push_back(atsitiktinisPazymys());

            A.exam = atsitiktinisPazymys();
            skaiciuoti(A);
            grupe.push_back(A);
            cout << "Prideta. Is viso studentu: " << grupe.size() << endl;
        }
        else if (p == 5) {
            if (grupe.empty()) {
                cout << "Grupe tuscia.\n";
            } else {
                rikiuoti(grupe);
                isvedimoPasirinkimas(grupe);
            }
        }
    }

    return 0;
}