#pragma once
#include <string>

struct EtapuLaikai {
    double nuskaitymo = 0.0;
    double rikiavimo = 0.0;
    double dalijimo = 0.0;
    double rasymo = 0.0;
    double bendras = 0.0;
};

struct TyrimoRezultatai {
    EtapuLaikai laikai;

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