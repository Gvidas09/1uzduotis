# Versija (v1.0)

## Projekto aprašymas

Tai C++ programa, skirta:

* studentų duomenų generavimui
* nuskaitymui iš failų
* galutinių pažymių skaičiavimui
* studentų rikiavimui
* skirstymui į dvi grupes
* skirtingų konteinerių ir strategijų spartos analizei

Projektas sukurtas remiantis ankstesne v0.4 versija ir išplėstas iki v1.0 reikalavimų.

---

## Naudojami konteineriai

* `std::vector`
* `std::list`
* `std::deque`

---

## Programos funkcionalumas

Programa leidžia:

* Generuoti testinius failus
* Nuskaityti duomenis iš failų
* Skaičiuoti galutinį pažymį (vidurkis / mediana)
* Rikiuoti studentus
* Skirstyti į grupes:

  * vargšiukai (< 5.0)
  * kietiakiai (≥ 5.0)
* Išsaugoti rezultatus į failus
* Atlikti spartos tyrimus
* Kartoti testus ir skaičiuoti vidurkius

---

## Galutinio pažymio formulės

```text
Galutinis (Vid.) = 0.4 * vidurkis + 0.6 * egzaminas
Galutinis (Med.) = 0.4 * mediana + 0.6 * egzaminas
```

---

## Studentų skirstymo strategijos

### 1 strategija

* Sukuriami du nauji konteineriai
* Studentai paskirstomi per vieną perėjimą

### 2 strategija

* Sukuriamas tik vienas konteineris (vargšiukai)
* Likę lieka pradiniame

### 3 strategija

* Naudojamas `stable_partition` principas
* Efektyvesnis duomenų padalijimas

---

## Rikiavimo kriterijai

1. Vardas
2. Pavardė
3. Galutinis (vidurkis)
4. Galutinis (mediana)

---

## Testiniai failai

* `studentai1000.txt`
* `studentai10000.txt`
* `studentai100000.txt`

---

## Matuojami laikai

* Nuskaitymas iš failo
* Rikiavimas
* Dalijimas į grupes
* Rašymas į failus
* Bendras veikimo laikas

---

## Tyrimo aplinka

| Komponentas    | Reikšmė              |
| -------------- | -------------------- |
| CPU            | Intel Core i7-10510U |
| RAM            | 16 GB DDR4           |
| Diskas         | SSD 512 GB           |
| OS             | Windows 10 Pro       |
| Kompiliatorius | g++                  |

---

## Tyrimo metodika

* Testuoti 3 konteineriai
* Testuotos 3 strategijos
* Kiekvienas testas kartotas 3 kartus
* Pateikiami vidutiniai laikai

---

# TYRIMO REZULTATAI

---

## std::vector

### 1000 įrašų

| Strategija | Nuskaitymas | Rikiavimas | Dalijimas | Rašymas | Bendras |
| ---------- | ----------- | ---------- | --------- | ------- | ------- |
| S1         | 0.029       | 0.003      | 0.007     | 0.008   | 0.048   |
| S2         | 0.032       | 0.003      | 0.008     | 0.008   | 0.052   |
| S3         | 0.030       | 0.004      | 0.032     | 0.049   | 0.115   |

### 10000 įrašų

| Strategija | Nuskaitymas | Rikiavimas | Dalijimas | Rašymas | Bendras |
| ---------- | ----------- | ---------- | --------- | ------- | ------- |
| S1         | 3.456       | 0.081      | 0.789     | 0.101   | 4.427   |
| S2         | 4.749       | 0.105      | 0.580     | 0.061   | 5.495   |
| S3         | 4.050       | 0.086      | 0.262     | 0.072   | 4.470   |

### 100000 įrašų

| Strategija | Nuskaitymas | Rikiavimas | Dalijimas | Rašymas | Bendras |
| ---------- | ----------- | ---------- | --------- | ------- | ------- |
| S1         | 16.253      | 1.632      | 0.128     | 0.806   | 18.819  |
| S2         | 22.276      | 1.442      | 0.087     | 0.489   | 24.294  |
| S3         | 59.565      | 4.258      | 0.470     | 2.305   | 66.597  |

---

## std::list

### 1000 įrašų

| Strategija | Nuskaitymas | Rikiavimas | Dalijimas | Rašymas | Bendras |
| ---------- | ----------- | ---------- | --------- | ------- | ------- |
| S1         | 0.414       | 0.001      | 0.076     | 0.015   | 0.507   |
| S2         | 0.468       | 0.001      | 0.000     | 0.161   | 0.630   |
| S3         | 0.446       | 0.001      | 0.075     | 0.010   | 0.532   |

### 10000 įrašų

| Strategija | Nuskaitymas | Rikiavimas | Dalijimas | Rašymas | Bendras |
| ---------- | ----------- | ---------- | --------- | ------- | ------- |
| S1         | 13.904      | 0.046      | 0.428     | 0.097   | 14.474  |
| S2         | 5.181       | 0.041      | 0.001     | 4.526   | 9.749   |
| S3         | 5.201       | 0.049      | 0.736     | 0.083   | 6.070   |

### 100000 įrašų

| Strategija | Nuskaitymas | Rikiavimas | Dalijimas | Rašymas | Bendras |
| ---------- | ----------- | ---------- | --------- | ------- | ------- |
| S1         | 98.198      | 1.904      | 0.765     | 3.272   | 104.138 |
| S2         | 7.917       | 0.519      | 0.017     | 0.532   | 8.984   |
| S3         | 9.363       | 0.543      | 0.276     | 0.771   | 10.952  |

---

## std::deque

### 1000 įrašų

| Strategija | Nuskaitymas | Rikiavimas | Dalijimas | Rašymas | Bendras |
| ---------- | ----------- | ---------- | --------- | ------- | ------- |
| S1         | 0.297       | 0.004      | 0.057     | 0.058   | 0.416   |
| S2         | 0.429       | 0.005      | 0.039     | 0.009   | 0.482   |
| S3         | 0.303       | 0.005      | 0.059     | 0.056   | 0.424   |

### 10000 įrašų

| Strategija | Nuskaitymas | Rikiavimas | Dalijimas | Rašymas | Bendras |
| ---------- | ----------- | ---------- | --------- | ------- | ------- |
| S1         | 5.226       | 0.135      | 0.909     | 0.117   | 6.386   |
| S2         | 4.614       | 0.101      | 0.700     | 0.067   | 5.482   |
| S3         | 3.469       | 0.102      | 0.698     | 0.084   | 4.354   |

### 100000 įrašų

| Strategija | Nuskaitymas | Rikiavimas | Dalijimas | Rašymas | Bendras |
| ---------- | ----------- | ---------- | --------- | ------- | ------- |
| S1         | 57.176      | 1.877      | 0.200     | 0.938   | 60.191  |
| S2         | 14.300      | 1.283      | 0.101     | 0.456   | 16.141  |
| S3         | 15.175      | 1.819      | 0.233     | 0.758   | 17.985  |

---

# Rezultatų analizė

Greičiausias konteineris: `std::vector`
Lėčiausias nuskaitymui: `std::list`
Balansuotas variantas: `std::deque`

Strategijos:

* 2 strategija – dažniausiai greičiausia
* 1 strategija – stabilus variantas
* 3 strategija – kai kur lėtesnė

---

## Projekto struktūra

* `main.cpp` – programos valdymas
* `Studentas.*` – studento logika
* `Failai.*` – failų operacijos
* `Rikiavimas.*` – rūšiavimas
* `Ivedimas.*` – vartotojo įvestis
* `Tyrimai.*` – spartos testai
* `CMakeLists.txt` – build sistema

---

## Kompiliavimas

### Su CMake

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### Su g++

```bash
g++ -std=c++17 -O2 main.cpp Studentas.cpp Failai.cpp Rikiavimas.cpp Ivedimas.cpp Tyrimai.cpp -o programa
```

---

## Paleidimas

```bash
./programa
```

---

## Išvada

* Geriausias bendras pasirinkimas: std::vector
* Efektyviausia strategija: 2 strategija
* Didėjant duomenų kiekiui skirtumai tarp konteinerių ryškėja

---

## Pastaba

Testai atlikti su realiais duomenimis, naudojant 3 kartojimus ir pateikiant vidurkius.
