# Studentų pažymių analizės programa (v2.0)

## Aprašymas

Ši programa skirta studentų duomenų apdorojimui: pažymių nuskaitymui, galutinio balo skaičiavimui, rūšiavimui bei studentų skirstymui į grupes. Projektas realizuotas naudojant C++17, laikantis objektinio programavimo principų.

v2.0 versijoje pridėta:

* **Unit testai** naudojant [doctest](https://github.com/doctest/doctest) framework (TDD principu)
* **Doxygen dokumentacija** — HTML ir LaTeX/PDF formatais
* Atnaujinta diegimo instrukcija per CMake

---

## Klasių hierarchija

| Klasė | Tipas | Aprašymas |
|---|---|---|
| `Zmogus` | Abstrakti bazinė | Saugo vardą ir pavardę; grynai virtualus destruktorius |
| `Studentas` | Išvestinė iš `Zmogus` | Namų darbų pažymiai, egzaminas, galutinis balas |

---

## Programos funkcionalumas

| # | Funkcija |
|---|---|
| 1 | Generuoti testinius studentų failus |
| 2 | Nuskaityti duomenis iš failo ir padalinti į grupes |
| 3 | Spartos tyrimas su skirtingais konteineriais ir strategijomis |
| 4 | v1.1 fiksuoto scenarijaus tyrimas |
| 5 | v1.5 paveldimumo ir abstrakčios klasės testai |
| 6 | Baigti |

---

## Naudojamos technologijos

| Technologija | Paskirtis |
|---|---|
| C++17 | Pagrindinis standartas |
| STL (`vector`, `list`, `deque`) | Konteineriai |
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

Po surinkimo `build/` kataloge bus du vykdomieji failai:

| Failas | Paskirtis |
|---|---|
| `studentu_programa` | Pagrindinė programa |
| `studentu_testai` | Unit testų vykdomasis failas |

---

## Paleidimas

```bash
# Pagrindinė programa
./build/studentu_programa

# Unit testai
./build/studentu_testai

# Unit testai per CTest
cd build && ctest --output-on-failure
```

---

## Unit testai

Testai parašyti TDD principu naudojant **doctest** framework. Testų failas: `tests/StudentasTestai.cpp`.

### Testuojamos sritys

| Sritis | Testų skaičius |
|---|---|
| Konstruktoriai ir Rule of Five | 9 |
| `Zmogus` abstrakcija ir paveldimumas | 2 |
| Skaičiavimai (vidurkis, mediana, galutinis) | 7 |
| Validacija (`arTinkamasPazymys`, exception) | 3 |
| `arVargsiukas` (abu kriterijai, riba) | 5 |
| Srautų operatoriai (`>>`, `<<`) | 6 |

### Testų paleidimo pavyzdys

```
[doctest] doctest version is "2.4.11"
[doctest] run with "--help" for options
===============================================================================
[doctest] test cases: 32 | 32 passed | 0 failed | 0 skipped
[doctest] assertions: 78 | 78 passed | 0 failed |
[doctest] Status: SUCCESS!
```

---

## Doxygen dokumentacija

Dokumentuotos klasės: `Zmogus` ir `Studentas` (failai `Zmogus.h`, `Studentas.h`).

### Dokumentacijos generavimas

```bash
# Per CMake (jei Doxygen įdiegtas)
cmake --build build --target dokumentacija

# Arba tiesiogiai
doxygen Doxyfile
```

Dokumentacija išvedama į `docs/` katalogą:

| Formatas | Katalogas | Pagrindinis failas |
|---|---|---|
| HTML | `docs/html/` | `docs/html/index.html` |
| LaTeX | `docs/latex/` | `docs/latex/refman.tex` |

PDF generavimas iš LaTeX:

```bash
cd docs/latex && make
```

---

## Failų struktūra

```
1uzduotis/
├── Zmogus.h / Zmogus.cpp        ← abstrakti bazinė klasė
├── Studentas.h / Studentas.cpp  ← pagrindinė klasė
├── Failai.h / Failai.cpp        ← failų I/O ir skirstymo strategijos
├── Rikiavimas.h / Rikiavimas.cpp← rikiavimo funkcijos
├── Ivedimas.h / Ivedimas.cpp    ← meniu ir vartotojo įvedimas
├── Tyrimai.h / Tyrimai.cpp      ← spartos tyrimai
├── Testai.h / Testai.cpp        ← v1.5 paveldimumo testai
├── main.cpp                     ← programos įėjimo taškas
├── tests/
│   └── StudentasTestai.cpp      ← doctest unit testai
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
| v2.0 | doctest unit testai, Doxygen dokumentacija |
| v1.5 | `Zmogus` abstrakti bazinė klasė, paveldimumas |
| v1.2 | Rule of Five, `operator>>`, `operator<<` |
| v1.1 | Spartos tyrimas su `vector`, `list`, `deque` |
| v1.0 | Pagrindinė studentų apdorojimo programa |

---

## Testų nuotraukos

<img width="669" height="215" alt="a96c972d-316f-4a67-a2a0-c6b2233996c8" src="https://github.com/user-attachments/assets/403eb59c-2b5c-4e3a-aed5-fb448570dc13" />
<img width="1160" height="1079" alt="a3fa14d9-eb37-4bd4-8e89-68321cc591fb" src="https://github.com/user-attachments/assets/7b381132-2ca3-450f-bc2d-a3acf8b21653" />
<img width="797" height="259" alt="51580366-0a00-4758-afbd-6c0eaed5d7f3" src="https://github.com/user-attachments/assets/8b8c9c7c-5c72-402c-9564-5ef8891d96ce" />
<img width="1760" height="1275" alt="7deb828e-2ac9-4c72-b534-b06857453045" src="https://github.com/user-attachments/assets/554c74cf-9747-49ca-9533-30c0f8da992b" />
<img width="927" height="1048" alt="7bc5e064-cc33-44b2-b879-d581d4495ea3" src="https://github.com/user-attachments/assets/ec54dc21-7555-40a2-a6cb-91069e3b87fb" />
<img width="1259" height="1130" alt="de8c6e1f-2fdf-4754-8975-5ff2a12520c2" src="https://github.com/user-attachments/assets/b6e48993-1207-47f6-b4c1-7352e2263401" />
<img width="874" height="375" alt="bf8a8eb3-fad3-46ea-ad75-d71c810ffb83" src="https://github.com/user-attachments/assets/fee7c1cb-a556-47ef-b599-d4cb0ff7b21b" />
