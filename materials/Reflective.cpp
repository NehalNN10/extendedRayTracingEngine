#include "Reflective.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Vector3D.hpp"

Reflective::Reflective(): Phong(), reflective_brdf(new Specular(0.9f, RGBColor(1.0f))) {}

Reflective::Reflective(const RGBColor& color): Phong(color), reflective_brdf(new Specular(0.9f, color)) {}

Reflective::Reflective(float ka, float kd, float ks, float exp, float kr, const RGBColor& color): Phong(ka, kd, ks, exp, color), reflective_brdf(new Specular(kr, color)) {}

Reflective::Reflective(const Reflective& other): Phong(other), reflective_brdf(new Specular(*other.reflective_brdf)) {}

Reflective& Reflective::operator=(const Reflective& other) {
    if (this == &other) return *this;
    
    Phong::operator=(other);
    
    if (reflective_brdf) delete reflective_brdf;
    reflective_brdf = new Specular(*other.reflective_brdf);
    
    return *this;
}

Reflective::~Reflective() {
    if (reflective_brdf) delete reflective_brdf;
}

bool Reflective::is_specular() const {
    return true;
}

RGBColor Reflective::sample_specular(const ShadeInfo& sinfo, const Vector3D& wo, Vector3D& wi) const {
    return reflective_brdf->sample_f(sinfo, wo, wi);
}

void Reflective::set_kr(float kr_val) {
    if (reflective_brdf) {
        reflective_brdf->set_kr(kr_val);
    }
}

void Reflective::set_cr(const RGBColor& color) {
    if (reflective_brdf) {
        reflective_brdf->set_cr(color);
    }
}