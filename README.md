# Studentų galutinio balo skaičiuoklė (v0.1)

## Programos aprašymas

Programa skirta studentų galutiniam balui apskaičiuoti. Ji nuskaito arba sugeneruoja studentų duomenis:

* vardą ir pavardę;
* namų darbų (ND) pažymius (1–10);
* egzamino pažymį (1–10).

Galutinis balas skaičiuojamas pagal formulę:

**Galutinis = 0.4 × ND + 0.6 × Egzaminas**

ND įvertinimui galima pasirinkti:

* vidurkį;
* medianą.

Rezultatai pateikiami ekrane su **dviejų skaičių po kablelio tikslumu**.

---

## Programos veikimas

Paleidus programą, pirmiausia pasirenkama skaičiavimo metodika:

```
V – skaičiuoti pagal vidurkį
M – skaičiuoti pagal medianą
```

Tuomet vartotojui pateikiamas meniu:

```
1 - Įvesti duomenis ranka
2 - Generuoti tik pažymius (vardas ir pavardė įvedami ranka)
3 - Generuoti vardą, pavardę ir pažymius automatiškai
4 - Baigti programos darbą
```

### 1 režimas

* Įvedamas studento vardas ir pavardė.
* Namų darbų pažymiai vedami po vieną.
* Įvedus **0**, pažymių įvedimas baigiamas.
* Įvedamas egzamino pažymys.

### 2 režimas

* Vardas ir pavardė įvedami ranka.
* Nurodomas ND kiekis.
* ND ir egzamino pažymiai sugeneruojami atsitiktinai (1–10).

### 3 režimas

* Vardas ir pavardė parenkami atsitiktinai.
* Nurodomas ND kiekis.
* ND ir egzamino pažymiai sugeneruojami atsitiktinai.

### 4 režimas

* Baigiamas duomenų įvedimas.
* Išvedama visų studentų galutinė suvestinė.

---

## Realizacijos versijos

Šioje versijoje pateiktos dvi programos realizacijos:

* **vektoriai.cpp** – naudojami tik `std::vector` konteineriai;
* **masyvai.cpp** – naudojami tik C kalbos masyvai (be `std::vector`).

---

## Įvedimo kontrolė

Programa tikrina vartotojo įvedimą:

* leidžiami tik skaičiai;
* pažymiai turi būti intervale **1–10**;
* meniu pasirinkimai turi būti nuo **1 iki 4**;
* neleidžiami neteisingi ar simboliniai įvedimai.

---

## Kompiliavimas ir paleidimas

Naudojant g++:

Vector versija:

```
g++ vektoriai.cpp -o programa
./programa
```

Masyvų versija:

```
g++ masyvai.cpp -o programa
./programa
```

---

## Versija

**v0.1**

Papildymai lyginant su v.pradinė:

* nežinomas studentų skaičius iš anksto;
* nežinomas namų darbų skaičius iš anksto;
* meniu su skirtingais darbo režimais;
* atsitiktinis duomenų generavimas;
* dvi realizacijos: C masyvai ir std::vector.
