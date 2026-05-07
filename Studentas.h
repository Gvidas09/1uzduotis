#pragma once
#include <string>
#include <vector>
#include <iosfwd>

#include "Zmogus.h"

/**
 * @brief Klasė, aprašanti studentą.
 *
 * Paveldi iš Zmogus. Saugo namų darbų pažymius ir egzamino pažymį,
 * skaičiuoja galutinius balus pagal vidurkį ir medianą.
 * Galutinis balas = 0.4 * ND_vidurkis + 0.6 * egzaminas.
 */
class Studentas : public Zmogus {
private:
    std::vector<int> paz_;  ///< Namų darbų pažymiai.
    int egz_;               ///< Egzamino pažymys.
    double gal_vid_;        ///< Galutinis balas pagal vidurkį.
    double gal_med_;        ///< Galutinis balas pagal medianą.

    /** @brief Apskaičiuoja namų darbų vidurkį. */
    double vidurkis() const;

    /**
     * @brief Patikrina, ar pažymys tinkamas (1–10).
     * @throws std::invalid_argument jei pažymys netinkamas.
     */
    void tikrintiPazymi(int pazymys) const;

    /**
     * @brief Patikrina visus pažymius vektoriuje.
     * @throws std::invalid_argument jei bent vienas netinkamas.
     */
    void tikrintiPazymius(const std::vector<int>& paz) const;

    /** @brief Išvalo studento duomenis (be vardo ir pavardės). */
    void isvalyti();

public:
    /** @brief Numatytasis konstruktorius. */
    Studentas();

    /**
     * @brief Konstruktorius su parametrais.
     * @param vardas   Studento vardas.
     * @param pavarde  Studento pavardė.
     * @param paz      Namų darbų pažymių vektorius (1–10).
     * @param egz      Egzamino pažymys (1–10).
     * @throws std::invalid_argument jei pažymiai už ribų.
     */
    Studentas(const std::string& vardas, const std::string& pavarde,
              const std::vector<int>& paz, int egz);

    /** @brief Kopijavimo konstruktorius. */
    Studentas(const Studentas& kitas);

    /** @brief Perkėlimo konstruktorius. */
    Studentas(Studentas&& kitas) noexcept;

    /** @brief Kopijavimo priskyrimo operatorius. */
    Studentas& operator=(const Studentas& kitas);

    /** @brief Perkėlimo priskyrimo operatorius. */
    Studentas& operator=(Studentas&& kitas) noexcept;

    /** @brief Destruktorius. */
    ~Studentas();

    /**
     * @brief Patikrina, ar pažymys patenka į leistinų ribas.
     * @param pazymys  Tikrinamas pažymys.
     * @return `true` jei pažymys yra nuo 1 iki 10.
     */
    static bool arTinkamasPazymys(int pazymys);

    /** @brief Grąžina namų darbų pažymių vektorių. */
    const std::vector<int>& pazymiai() const;

    /** @brief Grąžina egzamino pažymį. */
    int egzaminas() const;

    /** @brief Grąžina galutinį balą pagal vidurkį. */
    double galutinisVid() const;

    /** @brief Grąžina galutinį balą pagal medianą. */
    double galutinisMed() const;

    /**
     * @brief Nustato namų darbų pažymius ir perskaičiuoja galutinius.
     * @throws std::invalid_argument jei bent vienas pažymys netinkamas.
     */
    void nustatytiPazymius(const std::vector<int>& paz);

    /**
     * @brief Nustato egzamino pažymį ir perskaičiuoja galutinius.
     * @throws std::invalid_argument jei pažymys netinkamas.
     */
    void nustatytiEgzamina(int egz);

    /** @brief Apskaičiuoja namų darbų pažymių medianą. */
    double mediana() const;

    /** @brief Perskaičiuoja abu galutinius balus (vidurkio ir medianos). */
    void skaiciuotiGalutinius();

    /**
     * @brief Nustato, ar studentas yra „vargšiukas" (galutinis < 5).
     * @param naudoti_mediana  Jei `true`, naudoja medianą; kitaip — vidurkį.
     * @return `true` jei galutinis balas mažesnis nei 5.
     */
    bool arVargsiukas(bool naudoti_mediana = false) const;

    /**
     * @brief Įvesties operatorius.
     *
     * Iš `std::cin` — interaktyvus įvedimas su raginimu.
     * Iš kito srauto — nuskaitymas iš failo formato (viena eilutė).
     */
    friend std::istream& operator>>(std::istream& in, Studentas& studentas);

    /**
     * @brief Išvesties operatorius. Išveda vardą, pavardę ir abu galutinius balus.
     */
    friend std::ostream& operator<<(std::ostream& out, const Studentas& studentas);
};
