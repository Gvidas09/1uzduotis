#include <iostream>
#include <vector>
#include <string>
#include <chrono>

#include "Tyrimai.h"
#include "Studentas.h"
#include "Ivedimas.h"
#include "Failai.h"
#include "Rikiavimas.h"

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

using std::chrono::high_resolution_clock;
using std::chrono::duration;

void generuoti_visus_testinius_failus() {
    const int kiek_nd = 15;

    vector<string> failai = {
        "studentai1000.txt",
        "studentai10000.txt",
        "studentai100000.txt",
        "studentai1000000.txt",
        "studentai10000000.txt"
    };

    vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};

    cout << "\n1 TYRIMAS - failu kurimas ir uzdarymas\n";

    for (size_t i = 0; i < failai.size(); i++) {
        auto start = high_resolution_clock::now();
        bool ok = generuoti_studentu_faila(failai[i], dydziai[i], kiek_nd);
        auto end = high_resolution_clock::now();

        if (!ok) {
            cout << "Nepavyko sugeneruoti failo: " << failai[i] << endl;
            continue;
        }

        double laikas = duration<double>(end - start).count();
        cout << "Failo " << failai[i] << " sukurimo laikas: " << laikas << " s\n";
    }

    cout << "1 tyrimas baigtas.\n";
}

bool apdoroti_faila(const string& failas, int kriterijus, TyrimoRezultatai& rez) {
    vector<Studentas> visi;
    vector<Studentas> vargsiukai;
    vector<Studentas> kietiakiai;

    string vargsiuku_failas;
    string kietiaku_failas;
    sudaryti_rezultatu_failu_vardus(failas, vargsiuku_failas, kietiaku_failas);

    int praleista = 0;

    auto bendras_start = high_resolution_clock::now();

    auto start_nuskaityti = high_resolution_clock::now();
    bool ok = nuskaityti_is_failo(failas, visi, praleista);
    auto end_nuskaityti = high_resolution_clock::now();

    if (!ok) {
        return false;
    }

    auto start_dalinti = high_resolution_clock::now();
    padalinti_studentus(visi, vargsiukai, kietiakiai);
    auto end_dalinti = high_resolution_clock::now();

    auto start_rikiuoti = high_resolution_clock::now();
    rikiuoti(vargsiukai, kriterijus);
    rikiuoti(kietiakiai, kriterijus);
    auto end_rikiuoti = high_resolution_clock::now();

    auto start_rasyti = high_resolution_clock::now();
    isvesti_i_faila(vargsiukai, vargsiuku_failas);
    isvesti_i_faila(kietiakiai, kietiaku_failas);
    auto end_rasyti = high_resolution_clock::now();

    auto bendras_end = high_resolution_clock::now();

    rez.nuskaitymo_laikas = duration<double>(end_nuskaityti - start_nuskaityti).count();
    rez.dalijimo_laikas = duration<double>(end_dalinti - start_dalinti).count();
    rez.grupiu_rikiavimo_laikas = duration<double>(end_rikiuoti - start_rikiuoti).count();
    rez.rasymo_laikas = duration<double>(end_rasyti - start_rasyti).count();
    rez.bendras_laikas = duration<double>(bendras_end - bendras_start).count();

    rez.studentu_kiekis = (int)visi.size();
    rez.praleista = praleista;
    rez.vargsiuku_failas = vargsiuku_failas;
    rez.kietiaku_failas = kietiaku_failas;

    return true;
}

void spausdinti_rezultatus(const string& failas, const TyrimoRezultatai& rez) {
    cout << "\nFailas: " << failas << endl;
    cout << "Nuskaityta studentu: " << rez.studentu_kiekis << endl;
    cout << "Praleista eiluciu: " << rez.praleista << endl;
    cout << "Duomenu nuskaitymo is failo laikas: " << rez.nuskaitymo_laikas << " s\n";
    cout << "Studentu padalinimo i dvi grupes laikas: " << rez.dalijimo_laikas << " s\n";
    cout << "Grupiu rikiavimo laikas: " << rez.grupiu_rikiavimo_laikas << " s\n";
    cout << "Surikiuotu studentu isvedimo i du naujus failus laikas: " << rez.rasymo_laikas << " s\n";
    cout << "Visos programos veikimo laikas: " << rez.bendras_laikas << " s\n";
    cout << "Sukurti failai: " << rez.vargsiuku_failas << " ir " << rez.kietiaku_failas << endl;
}

void apdoroti_viena_faila() {
    string failas;
    cout << "Iveskite failo pavadinima: ";
    cin >> failas;

    int kriterijus = pasirinkti_rikiavimo_kriteriju();

    TyrimoRezultatai rez;
    bool ok = apdoroti_faila(failas, kriterijus, rez);

    if (!ok) {
        cout << "Failo apdoroti nepavyko.\n";
        return;
    }

    spausdinti_rezultatus(failas, rez);
}

void vykdyti_visu_failu_tyrima() {
    vector<string> failai = {
        "studentai1000.txt",
        "studentai10000.txt",
        "studentai100000.txt",
        "studentai1000000.txt",
        "studentai10000000.txt"
    };

    int kriterijus = pasirinkti_rikiavimo_kriteriju();

    cout << "\n2 TYRIMAS - duomenu apdorojimas naudojant jau sugeneruotus failus\n";

    for (const auto& failas : failai) {
        TyrimoRezultatai rez;
        bool ok = apdoroti_faila(failas, kriterijus, rez);

        if (!ok) {
            cout << "\nNepavyko apdoroti failo: " << failas << endl;
            continue;
        }

        spausdinti_rezultatus(failas, rez);
    }

    cout << "\n2 tyrimas baigtas.\n";
}