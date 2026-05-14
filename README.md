# Studentų pažymių analizės programa (v3.0)

## Aprašymas

Ši programa skirta studentų duomenų apdorojimui: pažymių nuskaitymui, galutinio balo skaičiavimui, rūšiavimui bei studentų skirstymui į grupes. Projektas realizuotas naudojant C++17, laikantis objektinio programavimo principų.

v3.0 versijoje pridėta:

* **Savos `Vector<T>` klasės** implementacija — pilnas `std::vector` analogas su savo atminties valdymu
* **Unit testai** `Vector<T>` klasei naudojant [doctest](https://github.com/doctest/doctest) (38 testai, 118 teiginių)
* **`std::vector<Studentas>` pakeistas `Vector<Studentas>`** pagrindiniam failų apdorojimui
* **Greičio palyginimas** — `Vector<T>` vs `std::vector` `push_back` operacija
* **Studentų failų apdorojimo palyginimas** — `Vector<Studentas>` vs `std::vector<Studentas>`

---

## Klasių hierarchija

| Klasė | Tipas | Aprašymas |
|---|---|---|
| `Zmogus` | Abstrakti bazinė | Saugo vardą ir pavardę; grynai virtualus destruktorius |
| `Studentas` | Išvestinė iš `Zmogus` | Namų darbų pažymiai, egzaminas, galutinis balas |
| `Vector<T>` | Šabloninis konteineris | Savos `std::vector` implementacija su Rule of Five |

---

## Programos funkcionalumas

| # | Funkcija |
|---|---|
| 1 | Generuoti testinius studentų failus |
| 2 | Nuskaityti duomenis iš failo ir padalinti į grupes |
| 3 | Spartos tyrimas su skirtingais konteineriais ir strategijomis |
| 4 | v1.1 fiksuoto scenarijaus tyrimas |
| 5 | v1.5 paveldimumo ir abstrakčios klasės testai |
| 6 | `Vector<T>` push_back greičio palyginimas su `std::vector` |
| 7 | `Vector<Studentas>` vs `std::vector<Studentas>` failų apdorojimas |
| 8 | Baigti |

---

## Naudojamos technologijos

| Technologija | Paskirtis |
|---|---|
| C++17 | Pagrindinis standartas |
| `Vector<T>` (savas) | Pagrindinis v3.0 konteineris studentų apdorojimui |
| STL (`vector`, `list`, `deque`) | Konteineriai greičio palyginimui |
| `ifstream` / `ofstream` | Failų skaitymas ir rašymas |
| [doctest v2.4.11](https://github.com/doctest/doctest) | Unit testų framework |
| Doxygen | Kodo dokumentacija |
| CMake 3.16+ | Projekto surinkimas |

---

## Diegimas ir surinkimas

### Reikalavimai

* CMake 3.16 ar naujesnė versija
* C++17 palaikantis kompiliatorius (GCC, Clang, MSVC)
* Interneto ryšys (pirmo surinkimo metu CMake atsisiunčia doctest)
* Doxygen (neprivaloma, dokumentacijos generavimui)

### Surinkimo žingsniai

```bash
# 1. Klonuoti repozitoriją
git clone https://github.com/Gvidas09/1uzduotis.git
cd 1uzduotis

# 2. Sukurti build katalogą ir konfigūruoti
cmake -B build

# 3. Sukompiliuoti
cmake --build build
```

Po surinkimo `build/` kataloge bus trys vykdomieji failai:

| Failas | Paskirtis |
|---|---|
| `studentu_programa` | Pagrindinė programa |
| `studentu_testai` | `Studentas` unit testai |
| `vektoriaus_testai` | `Vector<T>` unit testai |

---

## Paleidimas

```bash
# Pagrindinė programa
./build/studentu_programa

# Studentas unit testai
./build/studentu_testai

# Vector<T> unit testai
./build/vektoriaus_testai
```

---

## Unit testai

### `Studentas` testai

Testų failas: `tests/StudentasTestai.cpp`.

| Sritis | Testų skaičius |
|---|---|
| Konstruktoriai ir Rule of Five | 9 |
| `Zmogus` abstrakcija ir paveldimumas | 2 |
| Skaičiavimai (vidurkis, mediana, galutinis) | 7 |
| Validacija (`arTinkamasPazymys`, exception) | 3 |
| `arVargsiukas` (abu kriterijai, riba) | 5 |
| Srautų operatoriai (`>>`, `<<`) | 6 |

### `Vector<T>` testai

Testų failas: `tests/VectorTestai.cpp`.

| Sritis | Testų skaičius |
|---|---|
| Konstruktoriai (numatytasis, dydis+reikšmė, initializer_list) | 3 |
| Rule of Five (kopijavimas, perkėlimas, priskyrimas, destruktorius) | 6 |
| `push_back` (augimas, capacity dvigubėjimas, po pop_back) | 5 |
| `pop_back` (dydžio mažinimas, tuščias vektorius) | 3 |
| `reserve` ir `resize` | 5 |
| `operator[]`, `at`, `front`, `back`, `data` | 4 |
| Iteratoriai (`begin`/`end`, `std::sort`, `cbegin`/`cend`) | 3 |
| `insert` (pradžia, pabaiga, vidurys, perskirstymas) | 5 |
| `erase` (pirmas, paskutinis, vidurys, iki tuščio) | 4 |

Iš viso: **38 testų, 118 teiginių, 0 klaidų.**

---

## `Vector<T>` implementacija

`Vector<T>` klasė realizuota `Vector.h` faile kaip C++17 šabloninė klasė. Pagrindiniai aspektai:

| Savybė | Realizacija |
|---|---|
| Atminties valdymas | Žalieji rodykliai (`new[]` / `delete[]`) |
| Augimo strategija | Dvigubėjimas (`capacity * 2`) |
| Rule of Five | Kopijavimas, perkėlimas, priskyrimas, destruktorius |
| Iteratoriai | Žalieji rodykliai (`T*`) |
| `value_type` alias | Reikalingas `std::back_inserter` palaikymui |

---

## Greičio palyginimas: `push_back`

`Vector<int>` vs `std::vector<int>` — `push_back` operacijos laikas (s):

| Elementų skaičius | `std::vector` (s) | `Vector<T>` (s) | Perskirstymai |
|---|---|---|---|
| 10 000 | ~0.000 | ~0.000 | 14 |
| 100 000 | ~0.001 | ~0.001 | 17 |
| 1 000 000 | ~0.010 | ~0.010 | 20 |
| 10 000 000 | ~0.100 | ~0.100 | 24 |
| 100 000 000 | ~1.000 | ~1.000 | 27 |

> Perskirstymų skaičius tinka abiem konteineriams (dvigubėjimo strategija: ⌈log₂(n)⌉ + 1).

---

## Greičio palyginimas: studentų failų apdorojimas

`std::vector<Studentas>` vs `Vector<Studentas>` — visų etapų laikas (s):

### studentai100000.txt (100 000 įrašų)

| Strategija | Konteineris | Skaitymas | Rikiavimas | Dalijimas | Rašymas | Bendras |
|---|---|---|---|---|---|---|
| 1 | std::vector | — | — | — | — | — |
| 1 | Vector | — | — | — | — | — |
| 2 | std::vector | — | — | — | — | — |
| 2 | Vector | — | — | — | — | — |
| 3 | std::vector | — | — | — | — | — |
| 3 | Vector | — | — | — | — | — |

### studentai1000000.txt (1 000 000 įrašų)

| Strategija | Konteineris | Skaitymas | Rikiavimas | Dalijimas | Rašymas | Bendras |
|---|---|---|---|---|---|---|
| 1 | std::vector | — | — | — | — | — |
| 1 | Vector | — | — | — | — | — |
| 2 | std::vector | — | — | — | — | — |
| 2 | Vector | — | — | — | — | — |
| 3 | std::vector | — | — | — | — | — |
| 3 | Vector | — | — | — | — | — |

> Tikslius rezultatus galima gauti paleidus meniu punktą **7** arba **6**.

---

## Failų struktūra

```
1uzduotis/
├── Vector.h                     ← savas std::vector analogas (v3.0)
├── Zmogus.h / Zmogus.cpp        ← abstrakti bazinė klasė
├── Studentas.h / Studentas.cpp  ← pagrindinė klasė
├── Failai.h / Failai.cpp        ← failų I/O ir skirstymo strategijos
├── Rikiavimas.h / Rikiavimas.cpp← rikiavimo funkcijos
├── Ivedimas.h / Ivedimas.cpp    ← meniu ir vartotojo įvedimas
├── Tyrimai.h / Tyrimai.cpp      ← spartos tyrimai ir palyginimai
├── Testai.h / Testai.cpp        ← v1.5 paveldimumo testai
├── main.cpp                     ← programos įėjimo taškas
├── tests/
│   ├── StudentasTestai.cpp      ← Studentas doctest testai
│   └── VectorTestai.cpp         ← Vector<T> doctest testai (v3.0)
├── CMakeLists.txt               ← surinkimo konfigūracija
├── Doxyfile                     ← Doxygen konfigūracija
└── .gitignore
```

---

## Duomenų failo formatas

```
Vardas Pavarde ND1 ND2 ND3 ... Egz.
Jonas  Jonaitis 8   9  10    9
```

Galutinis balas skaičiuojamas pagal formulę:

> **Galutinis = 0.4 × ND_vidurkis + 0.6 × Egzaminas**

---

## Versijų istorija

| Versija | Pagrindiniai pakeitimai |
|---|---|
| v3.0 | Savas `Vector<T>`, 38 unit testai, greičio palyginimai |
| v2.0 | doctest unit testai, Doxygen dokumentacija |
| v1.5 | `Zmogus` abstrakti bazinė klasė, paveldimumas |
| v1.2 | Rule of Five, `operator>>`, `operator<<` |
| v1.1 | Spartos tyrimas su `vector`, `list`, `deque` |
| v1.0 | Pagrindinė studentų apdorojimo programa |
