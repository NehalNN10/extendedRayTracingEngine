#include "Specular.hpp"
#include "../../utilities/Vector3D.hpp"

Specular::Specular(): kr(0.0f), cr(RGBColor(0.0f)) {}

Specular::Specular(float kr_val, const RGBColor& cr_val): kr(kr_val), cr(cr_val) {}

Specular::Specular(const Specular& other): kr(other.kr), cr(other.cr) {}

Specular& Specular::operator=(const Specular& other) {
    if (this == &other) return *this;
    kr = other.kr;
    cr = other.cr;
    return *this;
}

RGBColor Specular::f(const ShadeInfo& sinfo, const Vector3D& wo, const Vector3D& wi) const {
    // sample_f for ray tracing
    return RGBColor(0.0f);
}

RGBColor Specular::rho(const ShadeInfo& sinfo, const Vector3D& wo) const {
    return RGBColor(0.0f);
}

RGBColor Specular::sample_f(const ShadeInfo& sinfo, const Vector3D& wo, Vector3D& wi) const {
    // wi = 2(n · wo)n - wo (reflection direction)
    
    float n_dot_wo = sinfo.normal * wo;
    wi = 2.0f * n_dot_wo * sinfo.normal - wo;
    
    // reflected radiance: kr * cr / (n · wi)
    return kr * cr / (sinfo.normal * wi);
}

float Specular::get_kr() const {
    return kr;
}

void Specular::set_kr(float kr_val) {
    kr = kr_val;
}

RGBColor Specular::get_cr() const {
    return cr;
}

void Specular::set_cr(const RGBColor& cr_val) {
    cr = cr_val;
}