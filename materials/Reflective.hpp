#pragma once

#include "Phong.hpp"
#include "BRDF/Specular.hpp"
#include "../utilities/RGBColor.hpp"

class Reflective : public Phong {
protected:
    Specular* reflective_brdf;  

public:
    Reflective();
    Reflective(const RGBColor& color);
    Reflective(float ka, float kd, float ks, float exp, float kr, const RGBColor& color);
    Reflective(const Reflective& other);
    Reflective& operator=(const Reflective& other);
    
    virtual ~Reflective();

    virtual bool is_specular() const override;
    virtual RGBColor sample_specular(const ShadeInfo& sinfo, const Vector3D& wo, Vector3D& wi) const override;

    void set_kr(float kr_val);
    void set_cr(const RGBColor& color);
};