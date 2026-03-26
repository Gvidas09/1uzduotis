#include "Tyrimai.h"
#include "Failai.h"
#include "Rikiavimas.h"
#include "Ivedimas.h"
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <chrono>
#include <iomanip>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::list;
using std::deque;
using std::cin;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

namespace {

const vector<string> TESTINIAI_FAILAI = {
    "studentai1000.txt",
    "studentai10000.txt",
    "studentai100000.txt",
    "studentai1000000.txt",
    "studentai10000000.txt"
};

const vector<int> TESTINIAI_DYDZIAI = {1000, 10000, 100000, 1000000, 10000000};
const int ND_KIEKIS = 15;

struct Vidurkiai {
    double nuskaitymo = 0.0;
    double rikiavimo = 0.0;
    double dalijimo = 0.0;
    double rasymo = 0.0;
    double bendras = 0.0;
};

template <typename Container>
bool apdoroti_faila_su_konteineriu(const string& failas, int kriterijus, int strategija, const string& konteinerio_vardas, TyrimoRezultatai& rez) {
    Container visi;
    Container vargsiukai;
    Container kietiakiai;

    int praleista = 0;
    bool naudoti_mediana = (kriterijus == 4);
    sudaryti_rezultatu_failu_vardus(failas, konteinerio_vardas, strategija, rez.vargsiuku_failas, rez.kietiaku_failas);

    auto bendras_start = high_resolution_clock::now();

    auto start_nuskaityti = high_resolution_clock::now();
    bool ok = nuskaityti_is_failo(failas, visi, praleista);
    auto end_nuskaityti = high_resolution_clock::now();
    if (!ok) return false;

    auto start_rikiuoti = high_resolution_clock::now();
    rikiuoti(visi, kriterijus);
    auto end_rikiuoti = high_resolution_clock::now();

    auto start_dalinti = high_resolution_clock::now();
    padalinti_studentus(visi, vargsiukai, kietiakiai, strategija, naudoti_mediana);
    auto end_dalinti = high_resolution_clock::now();

    auto start_rasyti = high_resolution_clock::now();
    bool ok1 = isvesti_i_faila(vargsiukai, rez.vargsiuku_failas);
    bool ok2 = isvesti_i_faila(kietiakiai, rez.kietiaku_failas);
    auto end_rasyti = high_resolution_clock::now();
    if (!ok1 || !ok2) return false;

    auto bendras_end = high_resolution_clock::now();

    rez.nuskaitymo_laikas = duration<double>(end_nuskaityti - start_nuskaityti).count();
    rez.rikiavimo_laikas = duration<double>(end_rikiuoti - start_rikiuoti).count();
    rez.dalijimo_laikas = duration<double>(end_dalinti - start_dalinti).count();
    rez.rasymo_laikas = duration<double>(end_rasyti - start_rasyti).count();
    rez.bendras_laikas = duration<double>(bendras_end - bendras_start).count();
    rez.studentu_kiekis = (int)(vargsiukai.size() + kietiakiai.size());
    rez.praleista = praleista;
    rez.strategija = strategija;
    rez.konteineris = konteinerio_vardas;

    return true;
}

bool apdoroti_faila_pagal_pasirinkima(const string& failas, int kriterijus, int strategija, int konteineris, TyrimoRezultatai& rez) {
    if (konteineris == 1) {
        return apdoroti_faila_su_konteineriu<vector<Studentas>>(failas, kriterijus, strategija, "vector", rez);
    }
    if (konteineris == 2) {
        return apdoroti_faila_su_konteineriu<list<Studentas>>(failas, kriterijus, strategija, "list", rez);
    }
    return apdoroti_faila_su_konteineriu<deque<Studentas>>(failas, kriterijus, strategija, "deque", rez);
}

void prideti_i_vidurkius(Vidurkiai& v, const TyrimoRezultatai& rez) {
    v.nuskaitymo += rez.nuskaitymo_laikas;
    v.rikiavimo += rez.rikiavimo_laikas;
    v.dalijimo += rez.dalijimo_laikas;
    v.rasymo += rez.rasymo_laikas;
    v.bendras += rez.bendras_laikas;
}

void padalinti_is_kiek(Vidurkiai& v, int kiek) {
    v.nuskaitymo /= kiek;
    v.rikiavimo /= kiek;
    v.dalijimo /= kiek;
    v.rasymo /= kiek;
    v.bendras /= kiek;
}

} // namespace

std::string gauti_konteinerio_varda(int pasirinkimas) {
    if (pasirinkimas == 1) return "vector";
    if (pasirinkimas == 2) return "list";
    if (pasirinkimas == 3) return "deque";
    return "visi";
}

std::string gauti_strategijos_varda(int strategija) {
    if (strategija == 1) return "1 strategija - du nauji konteineriai";
    if (strategija == 2) return "2 strategija - vienas naujas konteineris";
    if (strategija == 3) return "3 strategija - stable_partition principas";
    return "visos strategijos";
}

void generuoti_visus_testinius_failus() {
    cout << "\n1 TYRIMAS - failu kurimas ir uzdarymas\n";

    for (std::size_t i = 0; i < TESTINIAI_FAILAI.size(); i++) {
        auto start = high_resolution_clock::now();
        bool ok = generuoti_studentu_faila(TESTINIAI_FAILAI[i], TESTINIAI_DYDZIAI[i], ND_KIEKIS);
        auto end = high_resolution_clock::now();

        if (!ok) {
            cout << "Nepavyko sugeneruoti failo: " << TESTINIAI_FAILAI[i] << endl;
            continue;
        }

        double laikas = duration<double>(end - start).count();
        cout << "Failo " << TESTINIAI_FAILAI[i] << " sukurimo laikas: " << laikas << " s\n";
    }

    cout << "1 tyrimas baigtas.\n";
}

void spausdinti_rezultatus(const string& failas, const TyrimoRezultatai& rez, bool trumpai) {
    std::ios::fmtflags seni_flagai = cout.flags();
    std::streamsize senas_tikslumas = cout.precision();

    cout << std::fixed << std::setprecision(6);
    cout << "\nFailas: " << failas << '\n';
    cout << "Konteineris: std::" << rez.konteineris << '\n';
    cout << "Strategija: " << gauti_strategijos_varda(rez.strategija) << '\n';
    cout << "Nuskaityta studentu: " << rez.studentu_kiekis << '\n';
    cout << "Praleista eiluciu: " << rez.praleista << '\n';
    cout << "Duomenu nuskaitymo is failo laikas: " << rez.nuskaitymo_laikas << " s\n";
    cout << "Studentu rikiavimo konteineryje laikas: " << rez.rikiavimo_laikas << " s\n";
    cout << "Studentu padalinimo i dvi grupes laikas: " << rez.dalijimo_laikas << " s\n";
    cout << "Surikiuotu studentu isvedimo i du naujus failus laikas: " << rez.rasymo_laikas << " s\n";
    cout << "Visos programos veikimo laikas: " << rez.bendras_laikas << " s\n";
    if (!trumpai) {
        cout << "Sukurti failai: " << rez.vargsiuku_failas << " ir " << rez.kietiaku_failas << '\n';
    }

    cout.flags(seni_flagai);
    cout.precision(senas_tikslumas);
}

void apdoroti_viena_faila() {
    string failas;
    cout << "Iveskite failo pavadinima: ";
    cin >> failas;

    int kriterijus = pasirinkti_rikiavimo_kriteriju();
    int konteineris = pasirinkti_konteineri(false);
    int strategija = pasirinkti_strategija(false);

    TyrimoRezultatai rez;
    bool ok = apdoroti_faila_pagal_pasirinkima(failas, kriterijus, strategija, konteineris, rez);

    if (!ok) {
        cout << "Failo apdoroti nepavyko.\n";
        return;
    }

    spausdinti_rezultatus(failas, rez, false);
}

void vykdyti_visu_failu_tyrima() {
    int kriterijus = pasirinkti_rikiavimo_kriteriju();
    int konteineris = pasirinkti_konteineri(true);
    int strategija = pasirinkti_strategija(true);
    int kartojimai = ivesti_kieki("Kiek kartu kartoti kiekviena testa? ");

    cout << "\n2 TYRIMAS - duomenu apdorojimas naudojant jau sugeneruotus failus\n";

    int konteinerio_nuo = (konteineris == 4 ? 1 : konteineris);
    int konteinerio_iki = (konteineris == 4 ? 3 : konteineris);
    int strategijos_nuo = (strategija == 4 ? 1 : strategija);
    int strategijos_iki = (strategija == 4 ? 3 : strategija);

    for (const auto& failas : TESTINIAI_FAILAI) {
        for (int k = konteinerio_nuo; k <= konteinerio_iki; k++) {
            for (int s = strategijos_nuo; s <= strategijos_iki; s++) {
                Vidurkiai vid;
                TyrimoRezultatai paskutinis;
                bool pavyko = true;

                for (int i = 0; i < kartojimai; i++) {
                    TyrimoRezultatai rez;
                    if (!apdoroti_faila_pagal_pasirinkima(failas, kriterijus, s, k, rez)) {
                        pavyko = false;
                        break;
                    }
                    prideti_i_vidurkius(vid, rez);
                    paskutinis = rez;
                }

                if (!pavyko) {
                    cout << "\nNepavyko apdoroti failo: " << failas
                         << " naudojant std::" << gauti_konteinerio_varda(k)
                         << " ir " << gauti_strategijos_varda(s) << "\n";
                    continue;
                }

                padalinti_is_kiek(vid, kartojimai);
                paskutinis.nuskaitymo_laikas = vid.nuskaitymo;
                paskutinis.rikiavimo_laikas = vid.rikiavimo;
                paskutinis.dalijimo_laikas = vid.dalijimo;
                paskutinis.rasymo_laikas = vid.rasymo;
                paskutinis.bendras_laikas = vid.bendras;

                spausdinti_rezultatus(failas, paskutinis, true);
                cout << "Kartojimu skaicius: " << kartojimai << "\n";
                cout << "Paskutinio paleidimo sukurti failai: "
                     << paskutinis.vargsiuku_failas << " ir " << paskutinis.kietiaku_failas << "\n";
            }
        }
    }

    cout << "\n2 tyrimas baigtas.\n";
}