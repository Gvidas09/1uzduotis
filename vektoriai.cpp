#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>

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

int atsitiktinisPazymys() {
    return rand() % 10 + 1;
}

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
    cout << "Pasirinkimas: ";
    cin >> x;

    while (!cin || x < 1 || x > 4) {
        cout << "Klaida: iveskite skaiciu nuo 1 iki 4: ";
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
    }

    outputas(grupe);
    return 0;
}