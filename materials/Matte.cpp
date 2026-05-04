#include "Matte.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/Ray.hpp"
#include "../world/World.hpp"
#include "../lights/Light.hpp"

Matte::Matte(): ambient_brdf(new Lambertian(0.25f, RGBColor(1.0f))), diffuse_brdf(new Lambertian(0.75f, RGBColor(1.0f))) {}

Matte::Matte(const RGBColor& color): ambient_brdf(new Lambertian(0.25f, color)), diffuse_brdf(new Lambertian(0.75f, color)) {}

Matte::Matte(float ka, float kd, const RGBColor& color): ambient_brdf(new Lambertian(ka, color)), diffuse_brdf(new Lambertian(kd, color)) {}

Matte::Matte(const Matte& other): ambient_brdf(new Lambertian(*other.ambient_brdf)), diffuse_brdf(new Lambertian(*other.diffuse_brdf)) {}

Matte& Matte::operator=(const Matte& other) {
    if (this == &other) return *this;
    
    if (ambient_brdf) delete ambient_brdf;
    if (diffuse_brdf) delete diffuse_brdf;
    
    ambient_brdf = new Lambertian(*other.ambient_brdf);
    diffuse_brdf = new Lambertian(*other.diffuse_brdf);
    
    return *this;
}

Matte::~Matte() {
    if (ambient_brdf) delete ambient_brdf;
    if (diffuse_brdf) delete diffuse_brdf;
}

RGBColor Matte::shade(const ShadeInfo& sinfo) const {
    RGBColor L(0.0f);
    
    Vector3D wo = -sinfo.ray.d;
    wo.normalize();
    Vector3D wi(0.0f);
    
    L += ambient_brdf->rho(sinfo, wo) * sinfo.w->ambient_color * sinfo.w->ambient_intensity;
    
    if (sinfo.w && sinfo.w->lights.size() > 0) {
        for (const auto& light_ptr : sinfo.w->lights) {
            Vector3D light_dir = light_ptr->get_direction(sinfo.hit_point);
            light_dir.normalize();
            
            float n_dot_l = sinfo.normal * light_dir;
            
            // if facing the light
            if (n_dot_l > 0.0f) 
            {
                // adding small epsilon offset along normal to avoid self-intersection
                Point3D shadow_origin = sinfo.hit_point + kEpsilon * sinfo.normal;
                Ray shadow_ray(shadow_origin, light_dir);
                ShadeInfo shadow_info = sinfo.w->hit_objects(shadow_ray); // cast a shadow ray

                double light_distance = light_ptr->get_distance(sinfo.hit_point);
                
                // if the shadow ray hit something beyond the kEpsilon offset but before the light, then the point is obscured from light
                bool in_shadow = shadow_info.hit && shadow_info.t > kEpsilon && shadow_info.t < light_distance;
                if (in_shadow) 
                {
                    continue;
                }

                RGBColor brdf_contribution = diffuse_brdf->f(sinfo, wo, light_dir);
                
                RGBColor light_color = light_ptr->get_color() * light_ptr->get_intensity();
                double attenuation = light_ptr->get_attenuation(sinfo.hit_point);
                
                // L += light_color * brdf * (n·l) * attenuation
                L += light_color * brdf_contribution * n_dot_l * attenuation;
            }
        }
    }
    
    return L;
}

void Matte::set_ka(float ka_val) {
    if (ambient_brdf) {
        ambient_brdf->set_kd(ka_val);
    }
}

void Matte::set_kd(float kd_val) {
    if (diffuse_brdf) {
        diffuse_brdf->set_kd(kd_val);
    }
}

void Matte::set_cd(const RGBColor& color) {
    if (ambient_brdf) {
        ambient_brdf->set_cd(color);
    }
    if (diffuse_brdf) {
        diffuse_brdf->set_cd(color);
    }
}