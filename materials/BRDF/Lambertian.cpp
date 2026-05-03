#include "Lambertian.hpp"
#include "../../utilities/Constants.hpp"

Lambertian::Lambertian() : kd(0.0f), cd(RGBColor(0.0f)) {}

Lambertian::Lambertian(float kd_val, const RGBColor& cd_val): kd(kd_val), cd(cd_val) {}

Lambertian::Lambertian(const Lambertian& other): kd(other.kd), cd(other.cd) {}

Lambertian& Lambertian::operator=(const Lambertian& other) {
    if (this == &other) return *this;
    kd = other.kd;
    cd = other.cd;
    return *this;
}

RGBColor Lambertian::f(const ShadeInfo& sinfo, const Vector3D& wo, const Vector3D& wi) const {
    // f_r = (kd * cd) / pi
    return kd * cd * invPI;
}

RGBColor Lambertian::rho(const ShadeInfo& sinfo, const Vector3D& wo) const {
    // rho = kd * cd
    return kd * cd;
}

float Lambertian::get_kd() const {
    return kd;
}

void Lambertian::set_kd(float kd_val) {
    kd = kd_val;
}

RGBColor Lambertian::get_cd() const {
    return cd;
}

void Lambertian::set_cd(const RGBColor& cd_val) {
    cd = cd_val;
}