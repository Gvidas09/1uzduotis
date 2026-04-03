# Studentų pažymių apdorojimo ir analizės programa (v1.1)

## Aprašymas

Tai konsolinė C++ programa, skirta studentų duomenų apdorojimui ir programos veikimo spartos analizei dirbant su dideliais duomenų kiekiais.

### Programa gali:
- generuoti didelius studentų duomenų failus;
- nuskaityti studentų duomenis iš failo;
- suskirstyti studentus į dvi kategorijas pagal galutinį pažymį;
- rūšiuoti studentus pagal pasirinktą kriterijų;
- išvesti rezultatus į naujus failus;
- išmatuoti programos veikimo laiką skirtingais etapais.

## v1.1 pakeitimas

Pagrindinis v1.1 pakeitimas – Studentas duomenų tipas pakeistas iš struct į class.

### v1.1 versijoje:
- Studentas duomenys laikomi privačiuose laukuose;
- naudojami klasės metodai vietoje tiesioginio priėjimo prie laukų;
- realizuoti konstruktoriai;
- realizuotas destruktorius;
- galutinio balo skaičiavimas atliekamas klasės viduje.

Tokiu būdu realizacija tapo artimesnė objektinio programavimo principams ir geriau atitinka v1.1 užduoties reikalavimus.

## Galutinio pažymio skaičiavimas

Kiekvienam studentui saugoma:
- vardas
- pavardė
- namų darbų pažymiai
- egzamino pažymys

### Galutinis (Vid.)
```
Galutinis = 0.4 * namų darbų vidurkis + 0.6 * egzamino pažymys
```

### Galutinis (Med.)
```
Galutinis = 0.4 * namų darbų mediana + 0.6 * egzamino pažymys
```

Rezultatai pateikiami su dviem skaitmenimis po kablelio.

## Programos meniu

```
1 - Generuoti penkis testinius failus
2 - Apdoroti vieną failą
3 - Vykdyti spartos tyrimą visiems sugeneruotiems failams
4 - Vykdyti v1.1 fiksuotą tyrimą README lentelėms
5 - Baigti
```

## Testinių failų generavimas

Sugeneruojami failai:
```
studentai1000.txt
studentai10000.txt
studentai100000.txt
studentai1000000.txt
studentai10000000.txt
```

Formatas:
```
Vardas Pavarde ND1 ND2 ... ND15 Egz.
```

## Studentų skirstymas

### Vargšiukai
Galutinis pažymys < 5.0

### Kietiakiai
Galutinis pažymys >= 5.0

## Rūšiavimas

- vardą
- pavardę
- galutinį (vid.)
- galutinį (med.)

## Naudojami konteineriai

- std::vector
- std::list
- std::deque

## Tyrimo aplinka

| Komponentas | Reikšmė |
|------------|--------|
| CPU | Intel Core i7-10510U |
| RAM | 16 GB DDR4 |
| Diskas | SSD 512 GB |
| OS | Windows 10 Pro |
| Kompiliatorius | g++ |

## Programos paleidimas

```bash
cmake -B build
cmake --build build
```

## Tyrimas: v1.0 vs v1.1

### Rezultatų lentelė

| Versija | Failas | Konteineris | Strategija | Skaitymas | Rikiavimas | Dalijimas | Rašymas | Bendras |
|--------|--------|------------|-----------|----------|-----------|----------|---------|--------|
| v1.0 (struct) | studentai10000.txt | vector | 2 | 4.749000 | 0.105000 | 0.580000 | 0.061000 | 5.495000 |
| v1.1 (class) | studentai10000.txt | vector | 2 | 4.002652 | 0.101987 | 0.577632 | 0.061136 | 4.743407 |
| v1.0 (struct) | studentai100000.txt | vector | 2 | 22.276000 | 1.442000 | 0.087000 | 0.489000 | 24.294000 |
| v1.1 (class) | studentai100000.txt | vector | 2 | 16.022324 | 1.702426 | 0.102323 | 0.590966 | 18.418040 |

## Išvada

Pagal atliktą tyrimą, perėjimas nuo struct prie class nepablogino programos veikimo spartos.

- Su studentai10000.txt v1.1 veikė apie 13.7 % greičiau
- Su studentai100000.txt v1.1 veikė apie 24.2 % greičiau

Tai rodo, kad klasės panaudojimas nesukėlė neigiamo našumo efekto, o kodas tapo tvarkingesnis ir labiau atitinka objektinio programavimo principus.

## Tyrimas: kompiliatoriaus optimizacijos

### Rezultatų lentelė

| Optimizacija | Failas | Konteineris | Strategija | Skaitymas | Rikiavimas | Dalijimas | Rašymas | Bendras | EXE dydis |
|-------------|--------|------------|-----------|----------|-----------|----------|---------|--------|----------|
| O1 | studentai10000.txt | vector | 2 | 0.036514 | 0.007693 | 0.001243 | 0.032567 | 0.078018 | 215 KB |
| O2 | studentai10000.txt | vector | 2 | 0.034772 | 0.006855 | 0.001142 | 0.032651 | 0.075421 | 215 KB |
| O3 | studentai10000.txt | vector | 2 | 0.039207 | 0.008651 | 0.001601 | 0.037133 | 0.086594 | 216 KB |
| O1 | studentai100000.txt | vector | 2 | 0.511870 | 0.163151 | 0.020218 | 0.414156 | 1.109395 | 215 KB |
| O2 | studentai100000.txt | vector | 2 | 0.507750 | 0.159211 | 0.022322 | 0.439688 | 1.128971 | 215 KB |
| O3 | studentai100000.txt | vector | 2 | 0.643758 | 0.181787 | 0.023181 | 0.541895 | 1.396230 | 216 KB |

## Išvada

Gauti rezultatai parodė, kad didesnis optimizavimo lygis ne visada reiškia greitesnį veikimą.

- Su studentai10000.txt greičiausias buvo O2
- Su studentai100000.txt greičiausias buvo O1
- O3 abiem atvejais buvo lėčiausias

Vykdomojo failo dydis tarp O1 ir O2 nesiskyrė, o O3 buvo nežymiai didesnis.

Pagal šiuos rezultatus galima teigti, kad šiame projekte geriausią balansą tarp greičio ir vykdomojo failo dydžio suteikia O1 ir O2, o O3 papildomos naudos nesuteikė.

## Projekto struktūra

```
main.cpp – programos valdymas
Studentas.h, Studentas.cpp – studento klasė
Failai.h, Failai.cpp – failų operacijos
Rikiavimas.h, Rikiavimas.cpp – rūšiavimas
Ivedimas.h, Ivedimas.cpp – įvestis
Tyrimai.h, Tyrimai.cpp – testai
CMakeLists.txt – build sistema
```
