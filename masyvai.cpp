#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>

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

struct Studentas {
    string Vardas = "A";
    string Pavarde = "BB";
    vector<int> paz;
    int exam;
    double rez;
};

double mediana(vector<int> paz) {
    if (paz.size() == 0) return 0;

    sort(paz.begin(), paz.end());
    int n = paz.size();

    if (n % 2 == 1) return paz[n / 2];
    return (paz[n / 2 - 1] + paz[n / 2]) / 2.0;
}

void outputas(const vector<Studentas> &grupe, char pasirinkimas);


int atsitiktinisPazymys() {
    return rand() % 10 + 1; // 1..10
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
        cin.ignore(10000, '\n');
        cin >> x;
    }
    return x;
}

int ivestiSkaiciu(string tekstas, int nuo, int iki) {
    int x;
    cout << tekstas;
    cin >> x;

    while (!cin || x < nuo || x > iki) {
        cout << "Klaida: iveskite skaiciu nuo " << nuo << " iki " << iki << ": ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> x;
    }
    return x;
}

int ivestiKieki(string tekstas) {
    int x;
    cout << tekstas;
    cin >> x;

    while (!cin || x <= 0) {
        cout << "Klaida: skaicius turi buti bent 1. Iveskite dar karta: ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> x;
    }
    return x;
}

void skaiciuoti(Studentas &A, char pasirinkimas) {
    double vid = 0.0;

    if (A.paz.size() != 0) {
        int sum = 0;
        for (int x : A.paz) sum += x;
        vid = sum * 1.0 / (A.paz.size() * 1.0);
    }

    double med = mediana(A.paz);

    if (pasirinkimas == 'M' || pasirinkimas == 'm')
        A.rez = med * 0.4 + A.exam * 0.6;
    else
        A.rez = vid * 0.4 + A.exam * 0.6;
}


int main() {
    srand(time(NULL));

    Studentas A;
    vector<Studentas> grupe;

    char pasirinkimas;
    cout << "Skaiciuoti pagal (V)idurki ar (M)ediana? ";
    cin >> pasirinkimas;
    while (!cin || (pasirinkimas != 'V' && pasirinkimas != 'v' && pasirinkimas != 'M' && pasirinkimas != 'm')) {
        cout << "Klaida: iveskite tik V arba M: ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> pasirinkimas;
    }

    while (true) {
        int p = meniu();
        if (p == 4) break;

        A.paz.clear();

        if (p == 1) {
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
                    cin.ignore(10000, '\n');
                    cin >> temp;
                }

                if (temp == 0) break;

                while (!cin || temp < 1 || temp > 10) {
                    cout << "Klaida: pazymys turi buti 1-10. Iveskite dar karta: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cin >> temp;
                    if (temp == 0) break;
                }
                if (temp == 0) break;

                A.paz.push_back(temp);
            }

            A.exam = ivestiSkaiciu("Egzamino pazymys (1-10): ", 1, 10);

            skaiciuoti(A, pasirinkimas);
            grupe.push_back(A);
        }
        else if (p == 2) {
            cout << "Iveskite varda ir pavarde: ";
            cin >> A.Vardas >> A.Pavarde;

            int kiek = ivestiKieki("Kiek ND generuoti? ");
            for (int i = 0; i < kiek; i++) A.paz.push_back(atsitiktinisPazymys());

            A.exam = atsitiktinisPazymys();

            skaiciuoti(A, pasirinkimas);
            grupe.push_back(A);
        }
        else if (p == 3) {
            vector<string> vardai = {"Jonas","Ona","Ieva","Mantas","Egle","Tomas","Ruta","Paulius","Greta","Lukas"};
            vector<string> pavardes = {"Kazlauskas","Petrauskas","Jankauskas","Vaitkus","Zukauskas",
                                       "Stankevicius","Pocius","Noreika","Mikulenas","Sabonis"};

            A.Vardas = vardai[rand() % vardai.size()];
            A.Pavarde = pavardes[rand() % pavardes.size()];

            int kiek = ivestiKieki("Kiek ND generuoti? ");
            for (int i = 0; i < kiek; i++) A.paz.push_back(atsitiktinisPazymys());

            A.exam = atsitiktinisPazymys();

            skaiciuoti(A, pasirinkimas);
            grupe.push_back(A);
        }
    }

    outputas(grupe, pasirinkimas);
    return 0;
}

void outputas(const vector<Studentas> &grupe, char pasirinkimas) {
    if (pasirinkimas == 'M' || pasirinkimas == 'm') {
        cout << left << setw(10) << "Vardas"
             << left << setw(20) << "Pavarde"
             << setw(20) << "Galutinis (Med.)"
             << endl;
    } else {

        cout << left << setw(10) << "Vardas"
             << left << setw(20) << "Pavarde"
             << setw(20) << "Galutinis (Vid.)"
             << endl;
    }

    cout << "---------------------------------------------" << endl;

    for (auto A : grupe) {
        cout << left << setw(10) << A.Vardas
             << left << setw(20) << A.Pavarde
             << fixed << setprecision(2)
             << setw(20) << A.rez << endl;
    }
}
