#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::left;
using std::setw;

struct Studentas {
    string Vardas = "A";
    string Pavarde = "BB";
    vector<int> paz;
    int exam;
    double rez;
};

void outputas(const vector<Studentas> &grupe);

int main() {
    Studentas A;
    vector<Studentas> grupe;

    for (int ii = 0; ii < 2; ii++) {
        cout << "Iveskite varda ir pavarde: ";
        cin >> A.Vardas >> A.Pavarde;

        cout << "Iveskite semestro pazymius:\nKiek pazymiu bus? ";
        int n, temp, sum = 0;
        cin >> n;

        while (!cin || n <= 0) {
            cout << "Klaida: pazymiu skaicius turi buti bent 1. Iveskite dar karta: ";
            cin.clear();
            cin.ignore(10000, '\n');
            cin >> n;
        }

        for (int i = 0; i < n; i++) {
            cout << "Iveskite " << i + 1 << " pazymi is " << n << ": ";
            cin >> temp;
            A.paz.push_back(temp);
            sum += temp;
        }

        cout << "Iveskite egzamino paz: ";
        cin >> A.exam;

        A.rez = sum * 1.0 / (A.paz.size() * 1.0) * 0.4 + A.exam * 0.6;

        grupe.push_back(A);
        A.paz.clear();
    }

    outputas(grupe);
    return 0;
}

void outputas(const vector<Studentas> &grupe) {
    cout << left << setw(10) << "Vardas"
         << left << setw(20) << "Pavarde"
         << setw(20) << "Galutinis"
         << std::endl;

    cout << "---------------------------------------------" << std::endl;

    for (auto A : grupe) {
        cout << left << setw(10) << A.Vardas
             << left << setw(20) << A.Pavarde
             << std::fixed << std::setprecision(2)
             << setw(20) << A.rez << std::endl;
    }
}
