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

    // ambient + diffuse + specular + reflected rays
    virtual RGBColor shade(const ShadeInfo& sinfo) const override;

    void set_kr(float kr_val);
    void set_cr(const RGBColor& color);
};