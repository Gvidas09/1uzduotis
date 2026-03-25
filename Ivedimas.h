#pragma once
#include <string>

int ivesti_skaiciu(const std::string& tekstas, int nuo, int iki);
int ivesti_kieki(const std::string& tekstas);
int meniu();
int pasirinkti_rikiavimo_kriteriju();
int pasirinkti_konteineri(bool leisti_visus = false);
int pasirinkti_strategija(bool leisti_visas = false);