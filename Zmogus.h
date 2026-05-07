#pragma once
#include <string>

/**
 * @brief Abstrakti bazinė klasė, aprašanti žmogų.
 *
 * Saugo vardo ir pavardės duomenis. Negali būti tiesiogiai
 * instantanuota — naudojama kaip bazė išvestinėms klasėms.
 */
class Zmogus {
protected:
    std::string vardas_;   ///< Žmogaus vardas.
    std::string pavarde_;  ///< Žmogaus pavardė.

public:
    /** @brief Numatytasis konstruktorius. Inicializuoja tuščius laukus. */
    Zmogus();

    /**
     * @brief Konstruktorius su parametrais.
     * @param vardas   Žmogaus vardas.
     * @param pavarde  Žmogaus pavardė.
     */
    Zmogus(const std::string& vardas, const std::string& pavarde);

    /** @brief Kopijavimo konstruktorius. */
    Zmogus(const Zmogus& kitas);

    /** @brief Perkėlimo konstruktorius. */
    Zmogus(Zmogus&& kitas) noexcept;

    /** @brief Kopijavimo priskyrimo operatorius. */
    Zmogus& operator=(const Zmogus& kitas);

    /** @brief Perkėlimo priskyrimo operatorius. */
    Zmogus& operator=(Zmogus&& kitas) noexcept;

    /** @brief Grynai virtualus destruktorius — klasė abstrakti. */
    virtual ~Zmogus() = 0;

    /** @brief Grąžina vardą. */
    const std::string& vardas() const;

    /** @brief Grąžina pavardę. */
    const std::string& pavarde() const;

    /**
     * @brief Nustato vardą.
     * @param vardas  Naujas vardas.
     */
    void nustatytiVarda(const std::string& vardas);

    /**
     * @brief Nustato pavardę.
     * @param pavarde  Nauja pavardė.
     */
    void nustatytiPavarde(const std::string& pavarde);

protected:
    /** @brief Išvalo vardo ir pavardės laukus. */
    void isvalytiZmogausDuomenis();
};
