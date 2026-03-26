#include "Rikiavimas.h"
#include <algorithm>

namespace {

bool ar_skaitmuo(char c) {
    return c >= '0' && c <= '9';
}

int skaicius_gale(const std::string& s) {
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

std::string tekstas_be_galo_skaiciaus(const std::string& s) {
    int i = (int)s.size() - 1;
    if (i < 0) return s;
    if (!ar_skaitmuo(s[i])) return s;

    while (i >= 0 && ar_skaitmuo(s[i])) i--;
    return s.substr(0, i + 1);
}

} // namespace

bool palyginti_nat(const std::string& a, const std::string& b) {
    std::string ta = tekstas_be_galo_skaiciaus(a);
    std::string tb = tekstas_be_galo_skaiciaus(b);

    if (ta != tb) return ta < tb;

    int na = skaicius_gale(a);
    int nb = skaicius_gale(b);
    if (na != -1 && nb != -1) return na < nb;

    return a < b;
}

bool palyginti_pagal_varda(const Studentas& a, const Studentas& b) {
    if (a.vardas != b.vardas) return palyginti_nat(a.vardas, b.vardas);
    return palyginti_nat(a.pavarde, b.pavarde);
}

bool palyginti_pagal_pavarde(const Studentas& a, const Studentas& b) {
    if (a.pavarde != b.pavarde) return palyginti_nat(a.pavarde, b.pavarde);
    return palyginti_nat(a.vardas, b.vardas);
}

bool palyginti_pagal_vidurki(const Studentas& a, const Studentas& b) {
    if (a.gal_vid != b.gal_vid) return a.gal_vid < b.gal_vid;
    if (a.pavarde != b.pavarde) return palyginti_nat(a.pavarde, b.pavarde);
    return palyginti_nat(a.vardas, b.vardas);
}

bool palyginti_pagal_mediana(const Studentas& a, const Studentas& b) {
    if (a.gal_med != b.gal_med) return a.gal_med < b.gal_med;
    if (a.pavarde != b.pavarde) return palyginti_nat(a.pavarde, b.pavarde);
    return palyginti_nat(a.vardas, b.vardas);
}

static auto gauti_komparatoriu(int kriterijus) {
    if (kriterijus == 1) return &palyginti_pagal_varda;
    if (kriterijus == 2) return &palyginti_pagal_pavarde;
    if (kriterijus == 3) return &palyginti_pagal_vidurki;
    return &palyginti_pagal_mediana;
}

void rikiuoti(std::vector<Studentas>& grupe, int kriterijus) {
    if (grupe.empty()) return;
    std::sort(grupe.begin(), grupe.end(), gauti_komparatoriu(kriterijus));
}

void rikiuoti(std::deque<Studentas>& grupe, int kriterijus) {
    if (grupe.empty()) return;
    std::sort(grupe.begin(), grupe.end(), gauti_komparatoriu(kriterijus));
}

void rikiuoti(std::list<Studentas>& grupe, int kriterijus) {
    if (grupe.empty()) return;
    grupe.sort(gauti_komparatoriu(kriterijus));
}