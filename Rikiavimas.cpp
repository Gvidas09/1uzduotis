#include <iostream>
#include "Rikiavimas.h"
#include "Ivedimas.h"
#include <algorithm>
#include <string>

using std::string;
using std::vector;
using std::sort;

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
        std::cout << "Grupe tuscia - nera ka rikiuoti.\n";
        return;
    }

    std::cout << "\nRikiuoti studentus pagal:\n";
    std::cout << "1 - Varda\n";
    std::cout << "2 - Pavarde\n";
    std::cout << "3 - Galutini (Vid.)\n";
    std::cout << "4 - Galutini (Med.)\n";

    int r = ivesti_skaiciu("Pasirinkimas: ", 1, 4);

    if (r == 1) sort(grupe.begin(), grupe.end(), palyginti_pagal_varda);
    else if (r == 2) sort(grupe.begin(), grupe.end(), palyginti_pagal_pavarde);
    else if (r == 3) sort(grupe.begin(), grupe.end(), palyginti_pagal_vidurki);
    else sort(grupe.begin(), grupe.end(), palyginti_pagal_mediana);
}