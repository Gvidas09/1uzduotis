#pragma once
#include <string>
#include <vector>

struct Studentas {
    std::string vardas;
    std::string pavarde;
    std::vector<int> paz;
    int egz = 0;
    double gal_vid = 0.0;
    double gal_med = 0.0;
};

double mediana(const std::vector<int>& paz);
void skaiciuoti(Studentas& a);
bool ar_vargsiukas(const Studentas& a, bool naudoti_mediana = false);