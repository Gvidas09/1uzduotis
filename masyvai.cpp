#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using std::string;
using std::cin;
using std::cout;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;
using std::endl;
using std::sort;

const int MAX_PAZ = 100;     
const int MAX_STUD = 1000;   

struct Studentas {
    string Vardas = "A";
    string Pavarde = "BB";

    int paz[MAX_PAZ];
    int paz_kiek = 0;

    int exam;
    double rez;
};

double mediana(int paz[], int kiek) {
    if (kiek == 0) return 0;
    return 0;
}
void outputas(const Studentas grupe[], int grupe_kiek, char pasirinkimas);



int atsitiktinisPazymys() {
    return rand() % 10 + 1; 
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

    while (!cin || x <= 0 || x > MAX_PAZ) {
        cout << "Klaida: skaicius turi buti bent 1 ir ne daugiau kaip " << MAX_PAZ << ". Iveskite dar karta: ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> x;
    }
    return x;
}

void skaiciuoti(Studentas &A, char pasirinkimas) {
    double vid = 0.0;

    if (A.paz_kiek != 0) {
        int sum = 0;
        for (int i = 0; i < A.paz_kiek; i++) sum += A.paz[i];
        vid = sum * 1.0 / (A.paz_kiek * 1.0);
    }

    double med = mediana(A.paz, A.paz_kiek);

    if (pasirinkimas == 'M' || pasirinkimas == 'm')
        A.rez = med * 0.4 + A.exam * 0.6;
    else
        A.rez = vid * 0.4 + A.exam * 0.6;
}

int main() {
    srand(time(NULL));

    Studentas A;
    Studentas grupe[MAX_STUD];
    int grupe_kiek = 0;

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

        if (grupe_kiek >= MAX_STUD) {
            cout << "Pasiektas maksimalus studentu kiekis (" << MAX_STUD << ").\n";
            break;
        }

        A.paz_kiek = 0;

        cout << "Masyvu logika bus ideta sekanciame commite.\n";
    }

    outputas(grupe, grupe_kiek, pasirinkimas);
    return 0;
}

void outputas(const Studentas grupe[], int grupe_kiek, char pasirinkimas) {
    (void)grupe;
    (void)grupe_kiek;
    (void)pasirinkimas;
}
