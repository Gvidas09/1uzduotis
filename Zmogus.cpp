#include "Zmogus.h"
#include <utility>

Zmogus::Zmogus() : vardas_(""), pavarde_("") {}

Zmogus::Zmogus(const std::string& vardas, const std::string& pavarde)
    : vardas_(vardas), pavarde_(pavarde) {}

Zmogus::Zmogus(const Zmogus& kitas)
    : vardas_(kitas.vardas_), pavarde_(kitas.pavarde_) {}

Zmogus::Zmogus(Zmogus&& kitas) noexcept
    : vardas_(std::move(kitas.vardas_)), pavarde_(std::move(kitas.pavarde_)) {
    kitas.isvalytiZmogausDuomenis();
}

Zmogus& Zmogus::operator=(const Zmogus& kitas) {
    if (this != &kitas) {
        vardas_ = kitas.vardas_;
        pavarde_ = kitas.pavarde_;
    }
    return *this;
}

Zmogus& Zmogus::operator=(Zmogus&& kitas) noexcept {
    if (this != &kitas) {
        vardas_ = std::move(kitas.vardas_);
        pavarde_ = std::move(kitas.pavarde_);
        kitas.isvalytiZmogausDuomenis();
    }
    return *this;
}

Zmogus::~Zmogus() {}

const std::string& Zmogus::vardas() const { return vardas_; }
const std::string& Zmogus::pavarde() const { return pavarde_; }

void Zmogus::nustatytiVarda(const std::string& vardas) { vardas_ = vardas; }
void Zmogus::nustatytiPavarde(const std::string& pavarde) { pavarde_ = pavarde; }

void Zmogus::isvalytiZmogausDuomenis() {
    vardas_.clear();
    pavarde_.clear();
}