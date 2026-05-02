#include "Basic.hpp"
#include "../world/World.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../materials/Material.hpp"

RGBColor Basic::trace_ray(const Ray& ray) const {
    ShadeInfo sr = world_ptr->hit_objects(ray);
    
    if (sr.hit) {
        return sr.material_ptr->shade(sr);
    } else {
        return world_ptr->bg_color;
    }
}