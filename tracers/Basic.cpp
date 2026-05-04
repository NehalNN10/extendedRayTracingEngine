#include "Basic.hpp"
#include "../world/World.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../materials/Material.hpp"
#include "../utilities/Constants.hpp"
#include "../lights/Light.hpp"

RGBColor Basic::trace_ray(const Ray& ray, int depth) const {
    if (depth > world_ptr->max_depth) {
        return RGBColor(0.0f);
    }

    ShadeInfo sr = world_ptr->hit_objects(ray);
    sr.depth = depth;
    sr.ray = ray;

    if (!sr.hit) {
        return world_ptr->bg_color;
    }

    if (sr.normal * ray.d > 0.0f) {
        sr.normal = -sr.normal;
    }

    Vector3D wo = -ray.d;
    wo.normalize();

    RGBColor L = sr.material_ptr->rho(sr, wo) * world_ptr->ambient_color * world_ptr->ambient_intensity;

    for (Light* light : world_ptr->lights) {
        Vector3D wi = light->get_direction(sr.hit_point);
        wi.normalize();
        float n_dot_wi = sr.normal * wi;

        if (n_dot_wi > 0.0f) {
            RGBColor f = sr.material_ptr->f(sr, wo, wi);
            RGBColor light_color = light->get_color() * light->get_intensity();
            float attenuation = static_cast<float>(light->get_attenuation(sr.hit_point));
            L += f * light_color * (n_dot_wi * attenuation);
        }
    }

    if (sr.material_ptr->is_specular() && depth < world_ptr->max_depth) {
        Vector3D wi;
        RGBColor fr = sr.material_ptr->sample_specular(sr, wo, wi);
        Ray reflection_ray(sr.hit_point + kEpsilon * sr.normal, wi);
        L += fr * trace_ray(reflection_ray, depth + 1) * (sr.normal * wi);
    }

    return L;
}