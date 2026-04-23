#pragma once
#include <string>

class Zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    Zmogus();
    Zmogus(const std::string& vardas, const std::string& pavarde);
    Zmogus(const Zmogus& kitas);
    Zmogus(Zmogus&& kitas) noexcept;
    Zmogus& operator=(const Zmogus& kitas);
    Zmogus& operator=(Zmogus&& kitas) noexcept;
    virtual ~Zmogus() = 0;

    const std::string& vardas() const;
    const std::string& pavarde() const;

    void nustatytiVarda(const std::string& vardas);
    void nustatytiPavarde(const std::string& pavarde);

protected:
    void isvalytiZmogausDuomenis();
};