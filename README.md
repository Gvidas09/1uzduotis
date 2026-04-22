# Studentų pažymių analizės programa (v1.2)

## Aprašymas

Ši programa skirta studentų duomenų apdorojimui: pažymių nuskaitymui, galutinio balo skaičiavimui, rūšiavimui bei studentų skirstymui į grupes. Projektas realizuotas naudojant C++ kalbą, laikantis objektinio programavimo principų.

v1.2 versijoje pagrindinis dėmesys skirtas:

* `Studentas` klasės pilnam **Rule of Five** realizavimui
* įvesties (`>>`) ir išvesties (`<<`) operatorių perkrovimui
* šių funkcionalumų testavimui

---

## Naudojamos technologijos

* C++17 standartas
* STL konteineriai (`vector`, `list`, `deque`)
* Failų skaitymas ir rašymas (`ifstream`, `ofstream`)
* `stringstream` duomenų apdorojimui

---

## Programos funkcionalumas

Programa leidžia:

1. Generuoti testinius studentų failus
2. Nuskaityti duomenis iš failo
3. Apskaičiuoti galutinį pažymį:

   * pagal vidurkį
   * pagal medianą
4. Rūšiuoti studentus pagal:

   * vardą
   * pavardę
   * galutinį pažymį (vidurkį arba medianą)
5. Padalinti studentus į dvi grupes:

   * vargsiukai (galutinis < 5)
   * kietiakiai (galutinis ≥ 5)
6. Išvesti rezultatus į failus
7. Vykdyti automatinius v1.2 testus

---

## v1.2 patobulinimai

### Rule of Five realizacija

`Studentas` klasėje realizuoti visi būtini metodai:

* Numatytasis konstruktorius
* Konstruktorius su parametrais
* Kopijavimo konstruktorius
* Perkėlimo konstruktorius
* Kopijavimo priskyrimo operatorius
* Perkėlimo priskyrimo operatorius
* Destruktorius

Tai užtikrina teisingą objektų kūrimą, kopijavimą, perkėlimą ir išvalymą.

---

### Įvesties ir išvesties operatoriai

Realizuoti operatoriai:

#### `operator>>`

* Leidžia nuskaityti studentą iš:

  * failo eilutės
  * įvesties srauto
* Tikrina duomenų korektiškumą
* Netinkami duomenys pažymimi kaip klaida

#### `operator<<`

* Leidžia patogiai išvesti studento informaciją:

  * į ekraną
  * į failą
* Naudojamas rezultatų failų generavime

---

## Testavimas

Programoje įdiegtas testavimo mechanizmas (meniu punktas 5), kuris patikrina visus v1.2 reikalavimus.

### Testų rezultatai

```
[OK] Numatytasis konstruktorius
[OK] Konstruktorius su parametrais
[OK] Kopijavimo konstruktorius
[OK] Perkelimo konstruktorius
[OK] Kopijavimo priskyrimo operatorius
[OK] Perkelimo priskyrimo operatorius
[OK] Destruktorius
[OK] Isvesties operatorius <<
[OK] Ivesties operatorius >> is failo formato
[OK] Ivesties operatorius >> su blogais duomenimis
```

Visi testai sėkmingai įvykdyti.

---

## Testavimo scenarijai

### Failų generavimas

Sugeneruoti failai:

* studentai1000.txt
* studentai10000.txt
* studentai100000.txt
* studentai1000000.txt
* studentai10000000.txt

Pavyzdinis rezultatas:

```
Failo studentai1000.txt sukūrimo laikas: 0.0609782 s
Failo studentai10000.txt sukūrimo laikas: 0.0173738 s
Failo studentai100000.txt sukūrimo laikas: 0.184254 s
Failo studentai1000000.txt sukūrimo laikas: 1.65333 s
Failo studentai10000000.txt sukūrimo laikas: 18.4679 s
```

---

### Vieno failo apdorojimas

Naudotas failas:

* studentai1000.txt

Pasirinkimai:

* Rikiavimas: pagal galutinį pažymį (vidurkį)
* Konteineris: `std::vector`
* Strategija: 1 (du nauji konteineriai)

Rezultatai:

```
Nuskaityta studentu: 1000
Praleista eiluciu: 0
Duomenu nuskaitymo laikas: 0.047584 s
Studentu rikiavimo laikas: 0.002581 s
Padalinimo laikas: 0.000993 s
Isvedimo i failus laikas: 0.007709 s
Bendras veikimo laikas: 0.058867 s
```

Sukurti failai:

* studentai1000_vector_s1_vargsiukai.txt
* studentai1000_vector_s1_kietiakiai.txt

---

### Duomenų pavyzdžiai

#### Pradinio failo formatas

```
Vardas Pavarde ND1 ND2 ND3 ... Egz.
Vardas1 Pavarde1 3 10 6 4 5 ... 8
```

#### Kietiakiai

```
Vardas    Pavarde    Galutinis (Vid.)    Galutinis (Med.)
Vardas174 Pavarde174 5.00                4.60
...
```

#### Vargšiukai

```
Vardas    Pavarde    Galutinis (Vid.)    Galutinis (Med.)
Vardas46  Pavarde46  2.17                2.20
...
```

---

## Paleidimas

1. Sukompiliuoti projektą (per CMake arba VS Code)
2. Paleisti programą
3. Naudotis meniu:

```
1 - Generuoti failus
2 - Apdoroti failą
3 - Spartos tyrimas
4 - v1.1 tyrimas
5 - v1.2 testai
6 - Baigti
```

---

## Išvada

v1.2 versijoje sėkmingai realizuoti visi reikalavimai:

* Pilnai įgyvendinta Rule of Five
* Realizuoti ir panaudoti įvesties/išvesties operatoriai
* Sukurtas testavimo mechanizmas
* Programa išlieka funkcionali ir efektyvi

Testų nuotraukos:<img width="669" height="215" alt="a96c972d-316f-4a67-a2a0-c6b2233996c8" src="https://github.com/user-attachments/assets/403eb59c-2b5c-4e3a-aed5-fb448570dc13" />
<img width="1160" height="1079" alt="a3fa14d9-eb37-4bd4-8e89-68321cc591fb" src="https://github.com/user-attachments/assets/7b381132-2ca3-450f-bc2d-a3acf8b21653" />
<img width="797" height="259" alt="51580366-0a00-4758-afbd-6c0eaed5d7f3" src="https://github.com/user-attachments/assets/8b8c9c7c-5c72-402c-9564-5ef8891d96ce" />
<img width="1760" height="1275" alt="7deb828e-2ac9-4c72-b534-b06859453045" src="https://github.com/user-attachments/assets/554c74cf-9747-49ca-9533-30c0f8da992b" />
<img width="927" height="1048" alt="7bc5e064-cc33-44b2-b879-d581d4495ea3" src="https://github.com/user-attachments/assets/ec54dc21-7555-40a2-a6cb-91069e3b87fb" />
<img width="1259" height="1130" alt="de8c6e1f-2fdf-4754-8975-5ff2a12520c2" src="https://github.com/user-attachments/assets/b6e48993-1207-47f6-b4c1-7352e2263401" />
<img width="874" height="375" alt="bf8a8eb3-fad3-46ea-ad75-d71c810ffb83" src="https://github.com/user-attachments/assets/fee7c1cb-a556-47ef-b599-d4cb0ff7b21b" />

