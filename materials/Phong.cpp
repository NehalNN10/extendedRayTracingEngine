#include "Phong.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/Ray.hpp"
#include "../world/World.hpp"
#include "../lights/Light.hpp"

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

RGBColor Phong::shade(const ShadeInfo& sinfo) const {
    RGBColor L(0.0f);
    
    Vector3D wo = -sinfo.ray.d;
    wo.normalize();
    
    Vector3D wi_dummy(0.0f);
    L += ambient_brdf->rho(sinfo, wo) * sinfo.w->ambient_color * sinfo.w->ambient_intensity;

    if (sinfo.w && sinfo.w->lights.size() > 0) {
        for (const auto& light_ptr : sinfo.w->lights) {
            Vector3D light_dir = light_ptr->get_direction(sinfo.hit_point);
            light_dir.normalize();
            
            float n_dot_l = sinfo.normal * light_dir;
            
            if (n_dot_l > 0.0f) {
                Point3D shadow_origin = sinfo.hit_point + kEpsilon * sinfo.normal;
                Ray shadow_ray(shadow_origin, light_dir);
                ShadeInfo shadow_info = sinfo.w->hit_objects(shadow_ray);

                double light_distance = light_ptr->get_distance(sinfo.hit_point);
                bool in_shadow = shadow_info.hit && shadow_info.t > kEpsilon && shadow_info.t < light_distance;
                if (in_shadow) {
                    continue;
                }

                RGBColor light_color = light_ptr->get_color() * light_ptr->get_intensity();
                double attenuation = light_ptr->get_attenuation(sinfo.hit_point);
                
                RGBColor diffuse_contribution = diffuse_brdf->f(sinfo, wo, light_dir);
                RGBColor specular_contribution = specular_brdf->f(sinfo, wo, light_dir);
                
                // L += light_color * (diffuse + specular) * (n·l) * attenuation
                L += light_color * (diffuse_contribution + specular_contribution) * n_dot_l * attenuation;
            }
        }
    }
    
    return L;
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