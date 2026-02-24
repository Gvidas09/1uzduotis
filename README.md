# Studentų pažymių skaičiavimo programa (v0.2)

Tai konsolinė C++ programa, skirta studentų namų darbų ir egzamino pažymių apdorojimui. Programa leidžia įvesti studentų duomenis įvairiais būdais, automatiškai apskaičiuoja galutinius rezultatus pagal vidurkį ir medianą, suteikia galimybę rikiuoti studentus pagal pasirinktus kriterijus bei išvesti rezultatus į ekraną arba į failą. Ši versija (v0.2) papildyta duomenų nuskaitymu iš failo ir našumo matavimu.

Programoje kiekvienam studentui saugomas vardas, pavardė, namų darbų pažymiai ir egzamino rezultatas. Galutinis pažymys skaičiuojamas dviem būdais:

* Galutinis (Vid.) = 0.4 × namų darbų vidurkis + 0.6 × egzamino pažymys
* Galutinis (Med.) = 0.4 × namų darbų mediana + 0.6 × egzamino pažymys

Visi rezultatai pateikiami su dviem skaitmenimis po kablelio, o išvedimo lentelės stulpeliai yra gražiai išlygiuoti.

## Programos galimybės

Programa turi interaktyvų meniu, kuriame galima pasirinkti vieną iš šių veiksmų:

1. Įvesti studento duomenis ranka
   Vartotojas įveda vardą, pavardę ir namų darbų pažymius (1–10). Įvedus 0 pažymių vedimas baigiamas, po to įvedamas egzamino pažymys.

2. Generuoti tik pažymius
   Vartotojas suveda vardą ir pavardę, o namų darbų ir egzamino pažymiai sugeneruojami atsitiktinai.

3. Generuoti vardą, pavardę ir pažymius
   Vardas ir pavardė parenkami iš iš anksto paruošto sąrašo, o pažymiai sugeneruojami atsitiktinai.

4. Baigti programą

5. Nuskaityti studentus iš failo (v0.2)
   Programa nuskaito studentų duomenis iš tekstinio failo, apskaičiuoja rezultatus ir parodo nuskaitymo laiką. Jei failo eilutė yra neteisinga (trūksta duomenų, yra netinkamų simbolių ar pažymiai už ribų 1–10), ji praleidžiama ir suskaičiuojama kaip klaidinga.

6. Rikiuoti ir išvesti rezultatus
   Studentai gali būti rikiuojami pagal:

   * vardą
   * pavardę
   * galutinį pažymį pagal vidurkį
   * galutinį pažymį pagal medianą

Po rikiavimo rezultatai gali būti išvedami:

* į ekraną
* į failą (pvz. `rezultatai.txt`)

Jei studentų kiekis labai didelis (daugiau nei 10 000), programa perspėja, kad išvedimas į ekraną gali būti lėtas, ir rekomenduoja išvedimą į failą.

## Failo formatas

Duomenų failas turi būti tekstinis. Kiekviena eilutė turi tokią struktūrą:

Vardas Pavarde ND1 ND2 ND3 ... Egzaminas

Pavyzdys:

Vardas Pavarde ND1 ND2 ND3 ND4 Egzaminas
Jonas Jonaitis 8 9 10 7 9
Ona Onute 10 10 9 10 10
Ieva Ievute 6 7 8 9 8

Pirmi du laukai yra vardas ir pavardė, visi tolesni skaičiai yra pažymiai nuo 1 iki 10, o paskutinis skaičius laikomas egzamino pažymiu. Turi būti bent vienas namų darbas ir egzaminas. Jei failas turi antraštę („Vardas Pavarde ...“), ji automatiškai ignoruojama.

## Našumas

Skaitant duomenis iš failo, naudojama `std::chrono` biblioteka, kuri leidžia išmatuoti nuskaitymo laiką sekundėmis. Tai leidžia įvertinti programos veikimą su dideliais duomenų kiekiais.

## Kompiliavimas ir paleidimas

Linux / macOS:
g++ -std=c++17 -O2 -o studentai main.cpp
./studentai

Windows (MinGW):
g++ -std=c++17 -O2 -o studentai.exe main.cpp
studentai.exe

## Naudotos C++ bibliotekos

vector, string, algorithm, iomanip – duomenų saugojimui ir apdorojimui
fstream, sstream – darbui su failais
limits – įvedimo validacijai
chrono – veikimo laiko matavimui

## Versija

v0.2 – pridėtas studentų duomenų nuskaitymas iš failo, klaidingų eilučių tikrinimas, nuskaitymo laiko matavimas, rikiavimas pagal pasirinktus kriterijus ir galimybė išvesti rezultatus į ekraną arba į failą.
