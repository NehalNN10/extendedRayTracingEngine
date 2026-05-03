#pragma once

#include "BRDF.hpp"
#include <cmath>

class Glossy : public BRDF {
protected:
    float ks;
    RGBColor cs;
    float e;  // shininess

public:
    Glossy();
    Glossy(float ks_val, float exp_val, const RGBColor& cs_val);
    Glossy(const Glossy& other);
    Glossy& operator=(const Glossy& other);
    
    virtual ~Glossy() = default;

    virtual RGBColor f(const ShadeInfo& sinfo, const Vector3D& wo, const Vector3D& wi) const override;
    virtual RGBColor rho(const ShadeInfo& sinfo, const Vector3D& wo) const override;

    float get_ks() const;
    void set_ks(float ks_val);
    
    float get_exp() const;
    void set_exp(float exp_val);
    
    RGBColor get_cs() const;
    void set_cs(const RGBColor& cs_val);
};