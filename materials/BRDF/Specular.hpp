#pragma once

#include "BRDF.hpp"

class Specular : public BRDF {
protected:
    float kr;
    RGBColor cr;

public:
    Specular();
    Specular(float kr_val, const RGBColor& cr_val);
    Specular(const Specular& other);
    Specular& operator=(const Specular& other);
    
    virtual ~Specular() = default;

    // law of reflection: theta_i = theta_r
    // Dirac delta function in actual BRDF, but for ray tracing we use sample_f
    virtual RGBColor f(const ShadeInfo& sinfo, const Vector3D& wo, const Vector3D& wi) const override;
    virtual RGBColor rho(const ShadeInfo& sinfo, const Vector3D& wo) const override;
    virtual RGBColor sample_f(const ShadeInfo& sinfo, const Vector3D& wo, Vector3D& wi) const;

    float get_kr() const;
    void set_kr(float kr_val);
    
    RGBColor get_cr() const;
    void set_cr(const RGBColor& cr_val);
};