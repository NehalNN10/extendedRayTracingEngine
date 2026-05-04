#include "Phong.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Vector3D.hpp"

Phong::Phong(): ambient_brdf(new Lambertian(0.25f, RGBColor(1.0f))), diffuse_brdf(new Lambertian(0.75f, RGBColor(1.0f))), specular_brdf(new Glossy(0.5f, 32.0f, RGBColor(1.0f))) {}

Phong::Phong(const RGBColor& color): ambient_brdf(new Lambertian(0.25f, color)), diffuse_brdf(new Lambertian(0.75f, color)), specular_brdf(new Glossy(0.5f, 32.0f, color)) {}

Phong::Phong(float ka, float kd, float ks, float exp, const RGBColor& color): ambient_brdf(new Lambertian(ka, color)), diffuse_brdf(new Lambertian(kd, color)), specular_brdf(new Glossy(ks, exp, color)) {}

Phong::Phong(const Phong& other): ambient_brdf(new Lambertian(*other.ambient_brdf)), diffuse_brdf(new Lambertian(*other.diffuse_brdf)), specular_brdf(new Glossy(*other.specular_brdf)) {}

Phong& Phong::operator=(const Phong& other) {
    if (this == &other) return *this;
    
    if (ambient_brdf) delete ambient_brdf;
    if (diffuse_brdf) delete diffuse_brdf;
    if (specular_brdf) delete specular_brdf;
    
    ambient_brdf = new Lambertian(*other.ambient_brdf);
    diffuse_brdf = new Lambertian(*other.diffuse_brdf);
    specular_brdf = new Glossy(*other.specular_brdf);
    
    return *this;
}

Phong::~Phong() {
    if (ambient_brdf) delete ambient_brdf;
    if (diffuse_brdf) delete diffuse_brdf;
    if (specular_brdf) delete specular_brdf;
}

RGBColor Phong::f(const ShadeInfo& sinfo, const Vector3D& wo, const Vector3D& wi) const {
    return diffuse_brdf->f(sinfo, wo, wi) + specular_brdf->f(sinfo, wo, wi);
}

RGBColor Phong::rho(const ShadeInfo& sinfo, const Vector3D& wo) const {
    return ambient_brdf->rho(sinfo, wo);
}

void Phong::set_ka(float ka_val) {
    if (ambient_brdf) {
        ambient_brdf->set_kd(ka_val);
    }
}

void Phong::set_kd(float kd_val) {
    if (diffuse_brdf) {
        diffuse_brdf->set_kd(kd_val);
    }
}

void Phong::set_ks(float ks_val) {
    if (specular_brdf) {
        specular_brdf->set_ks(ks_val);
    }
}

void Phong::set_exp(float exp_val) {
    if (specular_brdf) {
        specular_brdf->set_exp(exp_val);
    }
}

void Phong::set_cd(const RGBColor& color) {
    if (ambient_brdf) {
        ambient_brdf->set_cd(color);
    }
    if (diffuse_brdf) {
        diffuse_brdf->set_cd(color);
    }
    if (specular_brdf) {
        specular_brdf->set_cs(color);
    }
}