#pragma once

#include "Material.hpp"
#include "BRDF/Lambertian.hpp"
#include "BRDF/Glossy.hpp"
#include "../utilities/RGBColor.hpp"

class Phong : public Material {
protected:
    Lambertian* ambient_brdf;
    Lambertian* diffuse_brdf;
    Glossy* specular_brdf;

public:
    Phong();
    Phong(const RGBColor& color);
    Phong(float ka, float kd, float ks, float exp, const RGBColor& color);
    Phong(const Phong& other);
    Phong& operator=(const Phong& other);
    
    virtual ~Phong();

    virtual RGBColor f(const ShadeInfo& sinfo, const Vector3D& wo, const Vector3D& wi) const override;
    virtual RGBColor rho(const ShadeInfo& sinfo, const Vector3D& wo) const override;

    void set_ka(float ka_val);
    void set_kd(float kd_val);
    void set_ks(float ks_val);
    void set_exp(float exp_val);
    void set_cd(const RGBColor& color);
};