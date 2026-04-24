# Studentų pažymių skaičiavimo programa (v1.5)

## Aprašymas

Ši programa skirta studentų duomenų apdorojimui: pažymių nuskaitymui, galutinio balo skaičiavimui, studentų rūšiavimui bei skirstymui į grupes.

v1.5 versijoje realizuotas objektinis modelis su paveldimumu:

* sukurta abstrakti bazinė klasė `Zmogus`
* klasė `Studentas` paveldi iš `Zmogus`
* pilnai išlaikytas v1.2 funkcionalumas

---

## v1.5 realizacija

### Bazinė klasė

Sukurta abstrakti klasė:

```
class Zmogus
```

* saugo bendrus duomenis: vardą ir pavardę
* turi virtualų (pure virtual) destruktorių
* **objekto sukurti negalima**

### Išvestinė klasė

```
class Studentas : public Zmogus
```

* paveldi vardą ir pavardę
* saugo pažymius ir egzaminą
* skaičiuoja:

  * galutinį (vid.)
  * galutinį (med.)

---

## Programos funkcionalumas

### 1. Failų generavimas

Sugeneruojami failai:

* studentai1000.txt
* studentai10000.txt
* studentai100000.txt
* studentai1000000.txt
* studentai10000000.txt

### 2. Duomenų apdorojimas

Atliekama:

* nuskaitymas iš failo
* rūšiavimas
* skirstymas į:

  * vargšiukus (<5)
  * kietiakus (>=5)

### 3. Strategijos

* 1 strategija – du nauji konteineriai
* 2 strategija – vienas naujas konteineris
* 3 strategija – `stable_partition`

### 4. Konteineriai

* `std::vector`
* `std::list`
* `std::deque`

---

## Testavimas (v1.5)

### Abstrakti klasė ir paveldimumas

```
[OK] Zmogus klase yra abstrakti
[OK] Studentas paveldi Zmogus duomenis
```

### Rule of Five

```
[OK] Numatytasis konstruktorius
[OK] Konstruktorius su parametrais
[OK] Kopijavimo konstruktorius
[OK] Perkelimo konstruktorius
[OK] Kopijavimo priskyrimo operatorius
[OK] Perkelimo priskyrimo operatorius
[OK] Destruktorius
```

### Operatoriai

```
[OK] Isvesties operatorius <<
[OK] Ivesties operatorius >> is failo formato
[OK] Ivesties operatorius >> su blogais duomenimis
```

---

## Spartos tyrimai

### Failų generavimas

| Failas     | Laikas (s) |
| ---------- | ---------- |
| 1 000      | 0.060      |
| 10 000     | 0.016      |
| 100 000    | 0.149      |
| 1 000 000  | 2.07       |
| 10 000 000 | 14.11      |

---

### Duomenų apdorojimas (vector, 1 strategija)

#### studentai1000.txt

| Veiksmas   | Laikas (s) |
| ---------- | ---------- |
| Skaitymas  | 0.034      |
| Rikiavimas | 0.0069     |
| Dalijimas  | 0.0011     |
| Rašymas    | 0.0086     |
| Bendras    | 0.0508     |

#### studentai10000.txt

| Veiksmas   | Laikas (s) |
| ---------- | ---------- |
| Skaitymas  | 1.479      |
| Rikiavimas | 0.115      |
| Dalijimas  | 0.598      |
| Rašymas    | 0.050      |
| Bendras    | 2.243      |

#### studentai100000.txt

| Veiksmas   | Laikas (s) |
| ---------- | ---------- |
| Skaitymas  | 5.859      |
| Rikiavimas | 1.526      |
| Dalijimas  | 0.065      |
| Rašymas    | 0.491      |
| Bendras    | 7.941      |

#### studentai1000000.txt

| Veiksmas   | Laikas (s) |
| ---------- | ---------- |
| Skaitymas  | 23.336     |
| Rikiavimas | 24.463     |
| Dalijimas  | 0.863      |
| Rašymas    | 6.344      |
| Bendras    | 55.006     |

#### studentai10000000.txt

| Veiksmas   | Laikas (s) |
| ---------- | ---------- |
| Skaitymas  | 247.961    |
| Rikiavimas | 371.619    |
| Dalijimas  | 10.186     |
| Rašymas    | 153.343    |
| Bendras    | 783.109    |

---

## v1.1 tyrimo rezultatai

| Failas  | Skaitymas | Rikiavimas | Dalijimas | Rašymas | Bendras |
| ------- | --------- | ---------- | --------- | ------- | ------- |
| 10 000  | 0.781     | 0.059      | 0.416     | 0.389   | 1.646   |
| 100 000 | 41.705    | 1.249      | 8.236     | 17.681  | 68.871  |

---

## Paleidimas

```bash
cmake -S . -B build
cmake --build build
.\build\studentu_programa.exe
```

---

## Meniu

```
1 - Generuoti failus
2 - Apdoroti failą
3 - Spartos tyrimai
4 - v1.1 tyrimas
5 - v1.5 testai
6 - Baigti
```

---

## Išvados

* v1.5 sėkmingai įgyvendintas paveldimumas
* abstrakti klasė veikia teisingai
* Studentas klasė pilnai suderinama su v1.2 funkcionalumu
* didžiausi laiko kaštai atsiranda rūšiavime
* programa korektiškai veikia su dideliais duomenų kiekiais

---
Testų nuotraukos:
<img width="817" height="258" alt="5dcc5c34-0195-40b0-a7e1-9f4ac654aadf" src="https://github.com/user-attachments/assets/2206cc08-acbd-4a5c-868f-e665748e02dc" />
<img width="730" height="343" alt="0af66f61-24c8-472c-b98d-39e3c0863594" src="https://github.com/user-attachments/assets/94226ac8-4aea-4dd1-b138-84b166e6da0b" />
<img width="812" height="333" alt="d58b7602-da04-4197-bd57-d5c873eba03b" src="https://github.com/user-attachments/assets/c3469500-6398-44b5-9186-cac559dfa055" />
<img width="1005" height="1037" alt="c35806cf-9732-4cec-a98a-0cf91e13a1e4" src="https://github.com/user-attachments/assets/0018a183-e0c6-435d-a068-d7005b09c4a4" />
<img width="823" height="841" alt="abf9c829-4b54-4724-ac62-412ba0f82e74" src="https://github.com/user-attachments/assets/fc6d101b-76a7-4a80-a768-071702e377b7" />
<img width="1169" height="856" alt="5702954a-f148-49f4-8474-0bfe9827d1f0" src="https://github.com/user-attachments/assets/5be43c74-8ce4-4e96-9dd7-6049f24ff5d6" />
<img width="1555" height="987" alt="70a0c5ac-fbd8-46c8-84c5-0db92d5dc79e" src="https://github.com/user-attachments/assets/1ae66d16-1369-46a4-bda5-2635e740f324" />
<img width="1648" height="764" alt="9ea19130-077f-46d0-9e85-143cf0308841" src="https://github.com/user-attachments/assets/97c670b1-ddd6-4208-bc38-c19a1efa8e0a" />
