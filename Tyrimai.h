#pragma once
#include <string>

struct TyrimoRezultatai {
    double failo_kurimo_laikas = 0.0;

    double nuskaitymo_laikas = 0.0;
    double dalijimo_laikas = 0.0;
    double grupiu_rikiavimo_laikas = 0.0;
    double rasymo_laikas = 0.0;
    double bendras_laikas = 0.0;

    int studentu_kiekis = 0;
    int praleista = 0;

    std::string vargsiuku_failas;
    std::string kietiaku_failas;
};

void generuoti_visus_testinius_failus();
bool apdoroti_faila(const std::string& failas, int kriterijus, TyrimoRezultatai& rez);
void spausdinti_rezultatus(const std::string& failas, const TyrimoRezultatai& rez);
void apdoroti_viena_faila();
void vykdyti_visu_failu_tyrima();