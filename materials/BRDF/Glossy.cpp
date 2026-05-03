#include "Glossy.hpp"
#include "../../utilities/Constants.hpp"
#include "../../utilities/Vector3D.hpp"

Glossy::Glossy(): ks(0.0f), e(1.0f), cs(RGBColor(0.0f)) {}

Glossy::Glossy(float ks_val, float exp_val, const RGBColor& cs_val): ks(ks_val), e(exp_val), cs(cs_val) {}

Glossy::Glossy(const Glossy& other): ks(other.ks), e(other.e), cs(other.cs) {}

Glossy& Glossy::operator=(const Glossy& other) {
    if (this == &other) return *this;
    ks = other.ks;
    e = other.e;
    cs = other.cs;
    return *this;
}

RGBColor Glossy::f(const ShadeInfo& sinfo, const Vector3D& wo, const Vector3D& wi) const {
    // Phong BRDF for glossy specular
    // f_r = ks * cs * (r · wo)^e
    // where r = 2(n · wi)n - wi (reflection direction)
    
    RGBColor L(0.0f);
    
    float n_dot_wi = sinfo.normal * wi;
    Vector3D r = 2.0f * n_dot_wi * sinfo.normal - wi;
    float r_dot_wo = r * wo;
    
    if (r_dot_wo > 0.0f) {
        L = ks * cs * std::pow(r_dot_wo, e);
    }
    
    return L;
}

RGBColor Glossy::rho(const ShadeInfo& sinfo, const Vector3D& wo) const {
    return RGBColor(0.0f);
}

float Glossy::get_ks() const {
    return ks;
}

void Glossy::set_ks(float ks_val) {
    ks = ks_val;
}

float Glossy::get_exp() const {
    return e;
}

void Glossy::set_exp(float exp_val) {
    e = exp_val;
}

RGBColor Glossy::get_cs() const {
    return cs;
}

void Glossy::set_cs(const RGBColor& cs_val) {
    cs = cs_val;
}