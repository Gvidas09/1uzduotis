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

struct V11TyrimoScenarijus {
    std::string failas;
    int kriterijus = 3;
    int konteineris = 1;
    int strategija = 1;
    int kartojimai = 1;
};

struct V11TyrimoEilute {
    std::string failas;
    std::string konteineris;
    int strategija = 0;
    int kartojimai = 0;
    EtapuLaikai vidutiniai_laikai;
};

std::string gauti_konteinerio_varda(int pasirinkimas);
std::string gauti_strategijos_varda(int strategija);

void generuoti_visus_testinius_failus();
void apdoroti_viena_faila();
void vykdyti_visu_failu_tyrima();
void vykdyti_v11_tyrima();
void vykdyti_vector_failu_tyrima();
void vykdyti_pushback_tyrima();
void spausdinti_rezultatus(const std::string& failas, const TyrimoRezultatai& rez, bool trumpai = false);
bool vykdyti_v11_scenariju(const V11TyrimoScenarijus& scenarijus, V11TyrimoEilute& eilute);