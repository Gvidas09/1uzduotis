# **Studentų pažymių apdorojimo ir analizės programa (v0.4)**

---

## *Aprašymas*

Tai **konsolinė C++ programa**, skirta **studentų pažymių duomenų apdorojimui** ir **programos veikimo spartos analizei** dirbant su **dideliais duomenų kiekiais**.

Programa gali:

- **generuoti didelius studentų duomenų failus**
- **nuskaityti studentų duomenis iš failo**
- **suskirstyti studentus į dvi kategorijas pagal galutinį pažymį**
- **rūšiuoti studentus pagal pasirinktą kriterijų**
- **išvesti rezultatus į naujus failus**
- **išmatuoti programos veikimo laiką skirtingais etapais**

> *Ši versija (v0.4) orientuota į programos efektyvumo analizę dirbant su labai dideliais duomenų rinkiniais.*

---

# **Galutinio pažymio skaičiavimas**

Kiekvienam studentui saugoma:

- **vardas**
- **pavardė**
- **namų darbų pažymiai**
- **egzamino pažymys**

Programa apskaičiuoja galutinį pažymį dviem būdais.

### **Galutinis (Vid.)**
Galutinis = 0.4 × namų darbų vidurkis + 0.6 × egzamino pažymys

### **Galutinis (Med.)**
Galutinis = 0.4 × namų darbų mediana + 0.6 × egzamino pažymys

Rezultatai pateikiami **su dviem skaitmenimis po kablelio**.

---

# **Programos meniu**
1 - Generuoti penkis testinius failus
2 - Apdoroti vieną failą
3 - Vykdyti spartos tyrimą visiems sugeneruotiems failams
4 - Baigti

---

# **Testinių failų generavimas**

Sugeneruojami failai:
studentai1000.txt
studentai10000.txt
studentai100000.txt
studentai1000000.txt
studentai10000000.txt

Kiekviena eilutė turi formatą:
Vardas Pavarde ND1 ND2 ND3 ... ND15 Egz.

### **Pavyzdys**
Vardas1 Pavarde1 8 5 9 7 6 10 4 8 9 7 6 8 5 9 10 7

---

# **Studentų skirstymas**

Studentai suskirstomi į dvi grupes.

### **Vargšiukai**
galutinis pažymys < 5.0

### **Kietiakiai**
galutinis pažymys ≥ 5.0

---

# **Rūšiavimas**

Studentai gali būti rūšiuojami pagal:

1. **vardą**
2. **pavardę**
3. **galutinį pažymį pagal vidurkį**
4. **galutinį pažymį pagal medianą**

Rūšiavimas atliekamas naudojant **std::sort** funkciją.

---

# **Rezultatų išvedimas**

Po apdorojimo sukuriami failai:
studentaiXXXX_vargsiukai.txt
studentaiXXXX_kietiakiai.txt

Pavyzdys:
studentai100000_vargsiukai.txt
studentai100000_kietiakiai.txt

---

# **Programos veikimo spartos analizė**

Atliekami **du tyrimai**.

## **1 tyrimas – failų kūrimas**

Matuojama:

- failo generavimas
- duomenų įrašymas
- failo uždarymas

## **2 tyrimas – duomenų apdorojimas**

Matuojama:

- duomenų nuskaitymas
- studentų skirstymas
- rūšiavimas
- rezultatų išvedimas
- bendras veikimo laikas
Laiko matavimui naudojama **std::chrono** biblioteka.
# **Programos testavimo rezultatai**<img width="1100" height="628" alt="v0,4 1" src="https://github.com/user-attachments/assets/748b4884-def9-445d-a080-fedb87025d07" />
<img width="1106" height="645" alt="v0,4 2" src="https://github.com/user-attachments/assets/cacc09d1-8c80-4890-8002-7e5dc1324f58" />
<img width="1110" height="641" alt="v0,4 3" src="https://github.com/user-attachments/assets/2cc0c49d-6162-460b-b3e5-8f0045d4ece3" />


