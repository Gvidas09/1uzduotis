# Studentų pažymių skaičiavimo programa (v0.3)

Tai konsolinė **C++** programa, skirta studentų namų darbų ir egzamino pažymių apdorojimui. Programa leidžia įvesti studentų duomenis įvairiais būdais, automatiškai apskaičiuoja galutinius rezultatus pagal **vidurkį** ir **medianą**, suteikia galimybę rikiuoti studentus pagal pasirinktus kriterijus bei išvesti rezultatus į ekraną arba į failą.

Ši versija (**v0.3**) papildyta kodo reorganizavimu (*refactoring*) ir išimčių valdymu (*Exception Handling*).

---

## Galutinio pažymio skaičiavimas

Programoje kiekvienam studentui saugomas:
- vardas
- pavardė
- namų darbų pažymiai
- egzamino pažymys

Galutinis pažymys skaičiuojamas dviem būdais:
Galutinis (Vid.) = 0.4 × namų darbų vidurkis + 0.6 × egzamino pažymys;
Galutinis (Med.) = 0.4 × namų darbų mediana + 0.6 × egzamino pažymys.

Rezultatai pateikiami su **dviem skaitmenimis po kablelio**, o lentelės stulpeliai yra išlygiuoti.

---

## Programos galimybės

Programa turi interaktyvų meniu, kuriame galima pasirinkti vieną iš šių veiksmų:

### 1 – Įvesti studento duomenis ranka
Vartotojas įveda vardą, pavardę ir namų darbų pažymius (1–10).  
Įvedus `0` pažymių vedimas baigiamas, po to įvedamas egzamino pažymys.

### 2 – Generuoti tik pažymius
Vartotojas įveda vardą ir pavardę, o namų darbų ir egzamino pažymiai sugeneruojami atsitiktinai.

### 3 – Generuoti vardą, pavardę ir pažymius
Vardas ir pavardė parenkami iš iš anksto paruošto sąrašo, o pažymiai sugeneruojami atsitiktinai.

### 4 – Baigti programą

### 5 – Nuskaityti studentus iš failo
Programa nuskaito studentų duomenis iš tekstinio failo, apskaičiuoja rezultatus ir parodo nuskaitymo laiką.

Jeigu:
- failas neegzistuoja,
- nepavyksta jo atidaryti,
- įvyksta skaitymo klaida,

klaidos apdorojamos naudojant `try/catch`.

Jeigu failo eilutė yra neteisinga (trūksta duomenų, yra netinkamų simbolių ar pažymiai už ribų 1–10), ji praleidžiama ir suskaičiuojama kaip klaidinga.

### 6 – Rikiuoti ir išvesti rezultatus

Studentai gali būti rikiuojami pagal:
- vardą
- pavardę
- galutinį pažymį pagal vidurkį
- galutinį pažymį pagal medianą

Rezultatai gali būti išvedami:
- į ekraną
- į failą (pvz. `rezultatai.txt`)

Jei studentų kiekis labai didelis (daugiau nei 10 000), programa perspėja, kad išvedimas į ekraną gali būti lėtas.

---

## Išimčių valdymas (v0.3)

Šioje versijoje naudojamas **C++ išimčių mechanizmas**:

- Netinkama skaitinė įvestis (pvz. raidės vietoje skaičiaus) gaudoma naudojant `try/catch`
- Netinkamos reikšmės (už leistinų ribų) apdorojamos su `std::out_of_range`
- Failų atidarymo ir rašymo klaidos gaudomos naudojant `std::ios_base::failure`

Visi klaidų pranešimai pateikiami lietuvių kalba.

---

## Kodo struktūra

Projektas suskaidytas į atskirus modulius:
Studentas.h / Studentas.cpp;
Ivedimas.h / Ivedimas.cpp;
Failai.h / Failai.cpp;
Rikiavimas.h / Rikiavimas.cpp;
main.cpp.

Naudojama `struct Studentas` duomenų saugojimui.

---

## Failo formatas

Duomenų failas turi būti tekstinis. Kiekviena eilutė turi tokią struktūrą:
Vardas Pavarde ND1 ND2 ND3 ... Egzaminas

- Pirmi du laukai yra vardas ir pavardė
- Visi tolesni skaičiai yra pažymiai nuo 1 iki 10
- Paskutinis skaičius laikomas egzamino pažymiu
- Turi būti bent vienas namų darbas ir egzaminas
- Jei failas turi antraštę („Vardas Pavarde ...“), ji automatiškai ignoruojama

---

## Našumas

Skaitant duomenis iš failo naudojama `std::chrono` biblioteka, kuri leidžia išmatuoti nuskaitymo laiką sekundėmis.

