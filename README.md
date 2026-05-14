# Studentų pažymių analizės programa (v3.0)

## Aprašymas

Ši programa skirta studentų duomenų apdorojimui: pažymių nuskaitymui, galutinio balo skaičiavimui, rūšiavimui bei studentų skirstymui į grupes. Projektas realizuotas naudojant C++17, laikantis objektinio programavimo principų.

Ši v3.0 versija yra ankstesnių v1.5/v2.0 projekto versijų tęsinys.

v3.0 versijoje pridėta:

* Savos `Vector<T>` klasės implementacija — `std::vector` tipo konteineris, padengiantis didžiąją dalį pagrindinio funkcionalumo
* Unit testai `Vector<T>` klasei naudojant [doctest](https://github.com/doctest/doctest)
* `std::vector<Studentas>` pakeistas `Vector<Studentas>` spartos tyrimuose
* Greičio palyginimas — `Vector<T>` vs `std::vector`
* Studentų failų apdorojimo palyginimas
* Doxygen dokumentacija
* CMake projektas
* Setup.exe diegimo paketo paruošimas naudojant Inno Setup

---

## Klasių hierarchija

| Klasė | Tipas | Aprašymas |
|---|---|---|
| `Zmogus` | Abstrakti bazinė | Saugo vardą ir pavardę; turi virtualų destruktorių |
| `Studentas` | Išvestinė klasė | Namų darbų pažymiai, egzaminas, galutinis balas |
| `Vector<T>` | Šabloninis konteineris | Savos realizacijos dinaminis konteineris |

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
| 8 | Baigti programą |

---

## Naudojamos technologijos

| Technologija | Paskirtis |
|---|---|
| C++17 | Pagrindinis standartas |
| `Vector<T>` | Savos realizacijos konteineris |
| STL (`vector`, `list`, `deque`) | Konteineriai palyginimams |
| `ifstream` / `ofstream` | Failų skaitymas ir rašymas |
| doctest | Unit testų framework |
| Doxygen | Dokumentacijos generavimas |
| CMake | Projekto surinkimas |
| Inno Setup | Setup.exe generavimas |

---

## Diegimas ir surinkimas

### Reikalavimai

* CMake 3.16+
* C++17 palaikantis kompiliatorius
* Git
* Doxygen (nebūtina)
* Inno Setup (nebūtina setup.exe generavimui)

---

### Projekto klonavimas

```bash
git clone https://github.com/Gvidas09/1uzduotis.git
cd 1uzduotis
```

### Surinkimas

```bash
cmake -B build
cmake --build build --config Release
```

---

## Paleidimas

```bash
./build/studentu_programa
```

Unit testai:

```bash
./build/studentu_testai
./build/vektoriaus_testai
```

---

## Unit testai

### `Studentas` testai

Testų failas: `tests/StudentasTestai.cpp`

| Sritis | Testų skaičius |
|---|---|
| Konstruktoriai ir Rule of Five | 9 |
| Paveldimumas ir abstrakcija | 2 |
| Galutinio balo skaičiavimai | 7 |
| Validacija ir exception | 3 |
| `arVargsiukas()` testai | 5 |
| Srautų operatoriai | 6 |

---

### `Vector<T>` testai

Testų failas: `tests/VectorTestai.cpp`

| Sritis | Testų skaičius |
|---|---|
| Konstruktoriai | 3 |
| Rule of Five | 6 |
| `push_back` | 5 |
| `pop_back` | 3 |
| `reserve` / `resize` | 5 |
| `operator[]`, `at`, `front`, `back` | 4 |
| Iteratoriai | 3 |
| `insert` | 5 |
| `erase` | 4 |

Iš viso:

* **38 testai**
* **118 teiginių**
* **0 klaidų**

---

# `Vector<T>` implementacija

`Vector<T>` realizuotas `Vector.h` faile kaip šabloninė C++17 klasė.

## Pagrindinės savybės

| Savybė | Realizacija |
|---|---|
| Atminties valdymas | `new[]` / `delete[]` |
| Augimo strategija | Capacity dvigubėjimas |
| Rule of Five | Pilnai realizuota |
| Iteratoriai | `T*` pagrindu |
| `value_type` | Palaikomas |

---

# `Vector<T>` naudojimo pavyzdžiai

## 1. `push_back`

```cpp
Vector<int> v;

v.push_back(10);
v.push_back(20);
v.push_back(30);
```

---

## 2. `reserve`

```cpp
Vector<int> v;

v.reserve(100);

for (int i = 0; i < 100; ++i)
    v.push_back(i);
```

---

## 3. `resize`

```cpp
Vector<int> v = {1, 2, 3};

v.resize(6, 99);
v.resize(2);
```

---

## 4. `insert`

```cpp
Vector<int> v = {1, 3, 4};

v.insert(v.begin() + 1, 2);
```

---

## 5. `erase`

```cpp
Vector<int> v = {10, 20, 30, 40};

v.erase(v.begin() + 1);
```

---

## 6. `at` ir `operator[]`

```cpp
Vector<int> v = {5, 10, 15};

int x = v[0];
int y = v.at(2);
```

---

## 7. `shrink_to_fit`

```cpp
Vector<int> v;

v.reserve(1000);

v.push_back(1);
v.push_back(2);

v.shrink_to_fit();
```

---

# Greičio palyginimas: `push_back`

`Vector<int>` vs `std::vector<int>`

| Elementų skaičius | `std::vector` (s) | `Vector<T>` (s) | `std::vector` persk. | `Vector` persk. |
|---|---|---|---|---|
| 10 000 | 0.000278 | 0.000144 | 15 | 15 |
| 100 000 | 0.002930 | 0.001571 | 18 | 18 |
| 1 000 000 | 0.025181 | 0.009547 | 21 | 21 |
| 10 000 000 | 0.246713 | 0.103607 | 25 | 25 |
| 100 000 000 | 2.656239 | 1.110131 | 28 | 28 |

> Abu konteineriai naudoja dvigubėjimo augimo strategiją (`capacity * 2`).

---

# Studentų failų apdorojimo palyginimas

## studentai100000.txt

| Strategija | Konteineris | Skaitymas | Rikiavimas | Dalijimas | Rašymas | Bendras |
|---|---|---|---|---|---|---|
| 1 | std::vector | 0.5025 | 1.0588 | 0.0349 | 0.2389 | 1.8350 |
| 1 | Vector | 0.6485 | 1.5131 | 0.0696 | 0.2881 | 2.5193 |
| 2 | std::vector | 0.7600 | 1.4534 | 0.0445 | 0.2745 | 2.5324 |
| 2 | Vector | 0.8281 | 1.7050 | 0.0623 | 0.2873 | 2.8828 |
| 3 | std::vector | 0.7896 | 1.5045 | 0.1002 | 0.2704 | 2.6647 |
| 3 | Vector | 0.8760 | 1.5919 | 0.1101 | 0.2854 | 2.8633 |

---

## studentai1000000.txt

| Strategija | Konteineris | Skaitymas | Rikiavimas | Dalijimas | Rašymas | Bendras |
|---|---|---|---|---|---|---|
| 1 | std::vector | 6.7690 | 22.0255 | 0.5339 | 3.5838 | 32.9123 |
| 1 | Vector | 8.2865 | 20.3472 | 0.6542 | 3.0310 | 32.3189 |
| 2 | std::vector | 6.8462 | 20.6628 | 0.4666 | 2.7872 | 30.7628 |
| 2 | Vector | 6.9422 | 20.2643 | 0.5504 | 2.9898 | 30.7466 |
| 3 | std::vector | 6.6424 | 20.2209 | 0.9084 | 2.7765 | 30.5482 |
| 3 | Vector | 6.8620 | 19.8426 | 1.0544 | 2.7935 | 30.5525 |

---

# Failų struktūra

```text
1uzduotis/
├── Vector.h
├── Studentas.h
├── Studentas.cpp
├── Zmogus.h
├── Failai.cpp
├── Failai.h
├── Tyrimai.cpp
├── Tyrimai.h
├── tests/
├── docs/
├── installer/
├── README.md
├── CMakeLists.txt
└── Doxyfile
```

---

# Duomenų failo formatas

```text
Vardas Pavarde ND1 ND2 ND3 ... Egz.
Jonas Jonaitis 8 9 10 9
```

Galutinio balo formulė:

```text
Galutinis = 0.4 * ND_vidurkis + 0.6 * Egzaminas
```

---

# Doxygen dokumentacija

Dokumentacija generuojama naudojant:

```bash
doxygen Doxyfile
```

Sugeneruoti HTML failai:

```text
docs/html/
```

---

# Setup.exe

Projektui paruoštas Inno Setup skriptas:

```text
setup.iss
```

Setup.exe sugeneravimas:

```bash
build_installer.bat
```

Diegimo paketas:

* sukuria Start Menu nuorodas,
* leidžia uninstall,
* įdiegia programą į `Program Files`,
* gali sukurti desktop shortcut.

---

# Versijų istorija

| Versija | Pakeitimai |
|---|---|
| v3.0 | Savos `Vector<T>` klasės realizacija, benchmarkai, testai |
| v2.0 | Unit testai ir Doxygen |
| v1.5 | Paveldimumas ir abstrakti klasė |
| v1.2 | Rule of Five |
| v1.1 | Spartos tyrimai |
| v1.0 | Pradinė programos versija |

---

# Autorius

**Gvidas Kučinskas**  
Vilniaus universitetas  
Objektinis programavimas (C++)
