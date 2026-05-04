#include "Matte.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Vector3D.hpp"

Matte::Matte(): ambient_brdf(new Lambertian(0.25f, RGBColor(1.0f))), diffuse_brdf(new Lambertian(0.75f, RGBColor(1.0f))) {}

Matte::Matte(const RGBColor& color): ambient_brdf(new Lambertian(0.25f, color)), diffuse_brdf(new Lambertian(0.75f, color)) {}

Matte::Matte(float ka, float kd, const RGBColor& color): ambient_brdf(new Lambertian(ka, color)), diffuse_brdf(new Lambertian(kd, color)) {}

Matte::Matte(const Matte& other): ambient_brdf(new Lambertian(*other.ambient_brdf)), diffuse_brdf(new Lambertian(*other.diffuse_brdf)) {}

Matte& Matte::operator=(const Matte& other) {
    if (this == &other) return *this;
    
    if (ambient_brdf) delete ambient_brdf;
    if (diffuse_brdf) delete diffuse_brdf;
    
    ambient_brdf = new Lambertian(*other.ambient_brdf);
    diffuse_brdf = new Lambertian(*other.diffuse_brdf);
    
    return *this;
}

Matte::~Matte() {
    if (ambient_brdf) delete ambient_brdf;
    if (diffuse_brdf) delete diffuse_brdf;
}

RGBColor Matte::f(const ShadeInfo& sinfo, const Vector3D& wo, const Vector3D& wi) const {
    return diffuse_brdf->f(sinfo, wo, wi);
}

RGBColor Matte::rho(const ShadeInfo& sinfo, const Vector3D& wo) const {
    return ambient_brdf->rho(sinfo, wo);
}

void Matte::set_ka(float ka_val) {
    if (ambient_brdf) {
        ambient_brdf->set_kd(ka_val);
    }
}

void Matte::set_kd(float kd_val) {
    if (diffuse_brdf) {
        diffuse_brdf->set_kd(kd_val);
    }
}

void Matte::set_cd(const RGBColor& color) {
    if (ambient_brdf) {
        ambient_brdf->set_cd(color);
    }
    if (diffuse_brdf) {
        diffuse_brdf->set_cd(color);
    }
}