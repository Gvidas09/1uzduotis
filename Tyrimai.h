#pragma once
#include <string>

struct TyrimoRezultatai {
    double failo_kurimo_laikas = 0.0;
    double nuskaitymo_laikas = 0.0;
    double rikiavimo_laikas = 0.0;
    double dalijimo_laikas = 0.0;
    double rasymo_laikas = 0.0;
    double bendras_laikas = 0.0;

    int studentu_kiekis = 0;
    int praleista = 0;
    int strategija = 0;
    std::string konteineris;

    std::string vargsiuku_failas;
    std::string kietiaku_failas;
};

std::string gauti_konteinerio_varda(int pasirinkimas);
std::string gauti_strategijos_varda(int strategija);

void generuoti_visus_testinius_failus();
void apdoroti_viena_faila();
void vykdyti_visu_failu_tyrima();
void spausdinti_rezultatus(const std::string& failas, const TyrimoRezultatai& rez, bool trumpai = false);