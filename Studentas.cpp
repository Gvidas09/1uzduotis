#include "Studentas.h"
#include <algorithm>
#include <stdexcept>
#include <utility>

Studentas::Studentas()
    : vardas_(""), pavarde_(""), paz_(), egz_(0), gal_vid_(0.0), gal_med_(0.0) {}

Studentas::Studentas(const std::string& vardas, const std::string& pavarde,
                     const std::vector<int>& paz, int egz)
    : vardas_(vardas), pavarde_(pavarde), paz_(paz), egz_(egz), gal_vid_(0.0), gal_med_(0.0) {
    tikrintiPazymius(paz_);
    tikrintiPazymi(egz_);
    skaiciuotiGalutinius();
}

Studentas::Studentas(const Studentas& kitas)
    : vardas_(kitas.vardas_), pavarde_(kitas.pavarde_), paz_(kitas.paz_),
      egz_(kitas.egz_), gal_vid_(kitas.gal_vid_), gal_med_(kitas.gal_med_) {}

Studentas::Studentas(Studentas&& kitas) noexcept
    : vardas_(std::move(kitas.vardas_)), pavarde_(std::move(kitas.pavarde_)),
      paz_(std::move(kitas.paz_)), egz_(kitas.egz_),
      gal_vid_(kitas.gal_vid_), gal_med_(kitas.gal_med_) {
    kitas.isvalyti();
}

Studentas& Studentas::operator=(const Studentas& kitas) {
    if (this != &kitas) {
        vardas_ = kitas.vardas_;
        pavarde_ = kitas.pavarde_;
        paz_ = kitas.paz_;
        egz_ = kitas.egz_;
        gal_vid_ = kitas.gal_vid_;
        gal_med_ = kitas.gal_med_;
    }
    return *this;
}

Studentas& Studentas::operator=(Studentas&& kitas) noexcept {
    if (this != &kitas) {
        vardas_ = std::move(kitas.vardas_);
        pavarde_ = std::move(kitas.pavarde_);
        paz_ = std::move(kitas.paz_);
        egz_ = kitas.egz_;
        gal_vid_ = kitas.gal_vid_;
        gal_med_ = kitas.gal_med_;
        kitas.isvalyti();
    }
    return *this;
}

Studentas::~Studentas() {
    isvalyti();
}

void Studentas::isvalyti() {
    vardas_.clear();
    pavarde_.clear();
    paz_.clear();
    egz_ = 0;
    gal_vid_ = 0.0;
    gal_med_ = 0.0;
}

bool Studentas::arTinkamasPazymys(int pazymys) {
    return pazymys >= 1 && pazymys <= 10;
}

const std::string& Studentas::vardas() const { return vardas_; }
const std::string& Studentas::pavarde() const { return pavarde_; }
const std::vector<int>& Studentas::pazymiai() const { return paz_; }
int Studentas::egzaminas() const { return egz_; }
double Studentas::galutinisVid() const { return gal_vid_; }
double Studentas::galutinisMed() const { return gal_med_; }

void Studentas::nustatytiVarda(const std::string& vardas) { vardas_ = vardas; }
void Studentas::nustatytiPavarde(const std::string& pavarde) { pavarde_ = pavarde; }

void Studentas::nustatytiPazymius(const std::vector<int>& paz) {
    tikrintiPazymius(paz);
    paz_ = paz;
    skaiciuotiGalutinius();
}

void Studentas::nustatytiEgzamina(int egz) {
    tikrintiPazymi(egz);
    egz_ = egz;
    skaiciuotiGalutinius();
}

void Studentas::tikrintiPazymi(int pazymys) const {
    if (!arTinkamasPazymys(pazymys)) {
        throw std::invalid_argument("Netinkamas pazymys");
    }
}

void Studentas::tikrintiPazymius(const std::vector<int>& paz) const {
    for (int pazymys : paz) {
        tikrintiPazymi(pazymys);
    }
}

double Studentas::vidurkis() const {
    if (paz_.empty()) return 0.0;

    long long suma = 0;
    for (int x : paz_) {
        suma += x;
    }

    return static_cast<double>(suma) / static_cast<double>(paz_.size());
}

double Studentas::mediana() const {
    if (paz_.empty()) return 0.0;

    std::vector<int> tmp = paz_;
    std::sort(tmp.begin(), tmp.end());

    int n = static_cast<int>(tmp.size());
    if (n % 2 == 1) return static_cast<double>(tmp[n / 2]);
    return (tmp[n / 2 - 1] + tmp[n / 2]) / 2.0;
}

void Studentas::skaiciuotiGalutinius() {
    double vid = vidurkis();
    double med = mediana();

    gal_vid_ = 0.4 * vid + 0.6 * static_cast<double>(egz_);
    gal_med_ = 0.4 * med + 0.6 * static_cast<double>(egz_);
}

bool Studentas::arVargsiukas(bool naudoti_mediana) const {
    return naudoti_mediana ? gal_med_ < 5.0 : gal_vid_ < 5.0;
}