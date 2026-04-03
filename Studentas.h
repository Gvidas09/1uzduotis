#pragma once
#include <string>
#include <vector>

class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<int> paz_;
    int egz_;
    double gal_vid_;
    double gal_med_;

public:
    Studentas();
    Studentas(const std::string& vardas, const std::string& pavarde,
              const std::vector<int>& paz, int egz);
    Studentas(const Studentas& kitas);
    Studentas(Studentas&& kitas) noexcept;
    Studentas& operator=(const Studentas& kitas);
    Studentas& operator=(Studentas&& kitas) noexcept;
    ~Studentas();

    const std::string& vardas() const;
    const std::string& pavarde() const;
    const std::vector<int>& pazymiai() const;
    int egzaminas() const;
    double galutinisVid() const;
    double galutinisMed() const;

    void nustatytiVarda(const std::string& vardas);
    void nustatytiPavarde(const std::string& pavarde);
    void nustatytiPazymius(const std::vector<int>& paz);
    void nustatytiEgzamina(int egz);

    double mediana() const;
    void skaiciuotiGalutinius();
    bool arVargsiukas(bool naudoti_mediana = false) const;
};