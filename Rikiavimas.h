#pragma once
#include <vector>
#include <list>
#include <deque>
#include <string>

#include "Studentas.h"

bool palyginti_nat(const std::string& a, const std::string& b);
bool palyginti_pagal_varda(const Studentas& a, const Studentas& b);
bool palyginti_pagal_pavarde(const Studentas& a, const Studentas& b);
bool palyginti_pagal_vidurki(const Studentas& a, const Studentas& b);
bool palyginti_pagal_mediana(const Studentas& a, const Studentas& b);

void rikiuoti(std::vector<Studentas>& grupe);
void rikiuoti(std::vector<Studentas>& grupe, int kriterijus);
void rikiuoti(std::list<Studentas>& grupe, int kriterijus);
void rikiuoti(std::deque<Studentas>& grupe, int kriterijus);