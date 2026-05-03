#pragma once

#include "BRDF.hpp"

class Lambertian : public BRDF {
protected:
    float kd;           // reflection coefficient
    RGBColor cd;        // albedo

public:
    Lambertian();
    Lambertian(float kd_val, const RGBColor& cd_val);
    Lambertian(const Lambertian& other);
    Lambertian& operator=(const Lambertian& other);
    
    virtual ~Lambertian() = default;

    virtual RGBColor f(const ShadeInfo& sinfo, const Vector3D& wo, const Vector3D& wi) const override;
    virtual RGBColor rho(const ShadeInfo& sinfo, const Vector3D& wo) const override;

    float get_kd() const;
    void set_kd(float kd_val);
    
    RGBColor get_cd() const;
    void set_cd(const RGBColor& cd_val);
};