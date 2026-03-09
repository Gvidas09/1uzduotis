#pragma once
#include <string>
#include <vector>
#include "Studentas.h"

bool nuskaityti_is_failo(const std::string& failas, std::vector<Studentas>& grupe, int& praleista);
void isvesti_i_faila(const std::vector<Studentas>& grupe, const std::string& failas);

bool generuoti_studentu_faila(const std::string& failas, int kiek_studentu, int kiek_nd);
void padalinti_studentus(const std::vector<Studentas>& visi,
                         std::vector<Studentas>& vargsiukai,
                         std::vector<Studentas>& kietiakiai);
void sudaryti_rezultatu_failu_vardus(const std::string& pradinis_failas,
                                     std::string& vargsiuku_failas,
                                     std::string& kietiaku_failas);