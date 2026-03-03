#pragma once
#include <string>
#include <vector>
#include "Studentas.h"

bool nuskaityti_is_failo(const std::string& failas, std::vector<Studentas>& grupe, int& praleista);
void isvesti_i_faila(const std::vector<Studentas>& grupe, const std::string& failas);