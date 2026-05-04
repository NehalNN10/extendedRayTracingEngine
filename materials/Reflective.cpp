#include "Reflective.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/Constants.hpp"
#include "../world/World.hpp"
#include "../lights/Light.hpp"

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

RGBColor Reflective::shade(const ShadeInfo& sinfo) const {
    
    RGBColor L = Phong::shade(sinfo);
    
    // reflect ray
    if (sinfo.depth < sinfo.w->max_depth) 
    {
        Vector3D wo = -sinfo.ray.d; // camera
        Vector3D wi; // will be set by sample_f
        
        // sample reflection direction from the BRDF
        RGBColor fr = reflective_brdf->sample_f(sinfo, wo, wi);
        
        // create reflection ray from hit point towards wi
        Ray reflection_ray(sinfo.hit_point + kEpsilon * sinfo.normal, wi);
        
        // recursively trace the reflection ray and get the reflected color
        RGBColor reflection_color = sinfo.w->tracer_ptr->trace_ray(reflection_ray, sinfo.depth + 1);
        
        // add weighted reflection to final color
        L += fr * reflection_color * (sinfo.normal * wi);
    }
    
    return L;
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