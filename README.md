# Studentų galutinio balo skaičiuoklė (v.pradinė)

## Aprašymas
Programa nuskaito studentų duomenis:
- vardą ir pavardę
- `n` namų darbų pažymių (1–10)
- egzamino pažymį (1–10)

Tada apskaičiuoja ir išveda galutinį balą, naudojant pasirinktą metodą:
- **vidurkį** arba
- **medianą**

Galutinio balo formulė:
- **Galutinis = 0.4 * ND + 0.6 * Egzaminas**

> Šioje `v.pradinė` versijoje studentų skaičius yra fiksuotas (įvedami 2 studentai).

---

## Funkcionalumas (kas padaryta v.pradinė)
- Pasirinkimas skaičiuoti pagal **vidurkį (V)** arba **medianą (M)**
- Įvedimo validacija:
  - leidžiami tik `V` / `M` (raidės)
  - pažymiai tik nuo **1 iki 10**
  - namų darbų skaičius turi būti **bent 1**
- Galutinis balas išvedamas su **2 skaičiais po kablelio**
- Rezultatai pateikiami lentelės formatu:
  - `Vardas`, `Pavarde`, `Galutinis (Vid.)` arba `Galutinis (Med.)`

---

## Kaip naudotis programa
1. Pasirink skaičiavimo metodą:
   - įvesk `V` (vidurkis) arba `M` (mediana)
2. Kiekvienam studentui:
   - įvesk vardą ir pavardę
   - įvesk namų darbų pažymių skaičių `n`
   - įvesk `n` pažymių (1–10)
   - įvesk egzamino pažymį (1–10)
3. Programa išves rezultatų lentelę.
