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
    vector<Studentas> grupe;
    outputas(grupe);
    return 0;
}

void outputas(const vector<Studentas> &grupe) {
    // kol kas nieko neisvedam
}
