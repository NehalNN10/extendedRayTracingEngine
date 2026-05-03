#pragma once

#include "Material.hpp"
#include "BRDF/Lambertian.hpp"
#include "../utilities/RGBColor.hpp"

class Matte : public Material {
protected:
    Lambertian* ambient_brdf;
    Lambertian* diffuse_brdf;

public:
    Matte();
    Matte(const RGBColor& color);
    Matte(float ka, float kd, const RGBColor& color);
    Matte(const Matte& other);
    Matte& operator=(const Matte& other);
    
    virtual ~Matte();

    virtual RGBColor shade(const ShadeInfo& sinfo) const override;

    void set_ka(float ka_val);
    void set_kd(float kd_val);
    void set_cd(const RGBColor& color);
};